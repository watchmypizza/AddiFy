#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <curl/curl.h>
#include <curl/easy.h>
#include <filesystem>
#include <fstream>
#include <random>
#include <regex>
#include <string>
#include <sys/types.h>
#include <vector>
#include <yaml-cpp/dll.h>
#include <yaml-cpp/exceptions.h>
#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/node/type.h>
#include <yaml-cpp/yaml.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include "../Include/typedefs.h"
#include "../Include/menu.h"

using json = nlohmann::json;

void RAMYAML(void);

YAML::Node configFile;

// load yaml
YAML::Node loadYaml(const str_t& path) {
    if(!configFile.IsNull()) {
        return configFile;
    }
    try {
        configFile = YAML::LoadFile(path);
        return configFile;
    } catch(YAML::Exception& e) {
        std::cerr << "Error parsing YAML file: " << e.what() << std::endl;
        RAMYAML();
        return YAML::Node();
    }
}

strlist_t parseAlbumTracks(const str_t& rawJsonResponse);
int addToPlaylist(strlist_t& trackIds);
strlist_t getArtistDiscography(void);
int getAlbumNameAndTracks(void);
strlist_t makeTrackIdUnique(const strlist_t& trackIds);
void printMessage(const str_t& message);
str_t searchSuggestions(const str_t& artistName);
bool compareArtistName(const str_t& s1, const str_t& s2, double threshold);
size_t levenshteins_distance(const str_t& s1, const str_t& s2);

bool isDebug = false;
bool allowDuplicates = false;
bool allowChunking = true;
bool launchedMenu = false;

void RAMYAML(void) {
    auto tempPath = std::filesystem::temp_directory_path() / "addify_runtime.yaml";

    std::ofstream outFile(tempPath);
    if(outFile.is_open()) {
        outFile << "# === AddiFy Live Runtime YAML Configuration ===\n"
                << "# Nothing here gets saved permanently, all of this lives inside of RAM\n"
                << "authorization-bearer: \n"
                << "client-token: \n"
                << "\n"
                << "artists: # You can add as many artists as you want by adding new dashes in each new line\n"
                << "  - \n"
                << "\n"
                << "render-ahead-limit: 40\n"
                << "playlist-to-add-to: \n";
        outFile.close();
    }

    const char *editor = std::getenv("EDITOR");
    if(!editor) editor = "nano";

    str_t cmd = str_t(editor) + " " + tempPath.string();
    std::system(cmd.c_str());

    try{
        configFile = YAML::LoadFile(tempPath.string());
        std::filesystem::remove(tempPath);

        getAlbumNameAndTracks();
        return;
    } catch(YAML::Exception e) {
        std::filesystem::remove(tempPath);
        std::cerr << "YAML Encountered a parsing error: " << e.what() << std::endl;
        return;
    }
    return;
}

void printProgressBar(size_t current, size_t total, std::chrono::steady_clock::time_point startTime) {
    if(total == 0) return;
    if(isDebug) return;

    int percent = static_cast<int>((static_cast<double>(current) / total) * 100);

    const int barWidth = 30;
    int progress = static_cast<int>((static_cast<double>(current) / total) * barWidth);

    std::cout << "\r[";
    for(int i = 0; i < barWidth; ++i) {
        if(i < progress - 1) {
            std::cout << "=";
        } else if(i == progress - 1) {
            std::cout << ">";
        } else {
            std::cout << " ";
        }
    }
    std::cout << "]" << std::setw(3) << percent << "% ";

    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
    long minutes = elapsedSeconds / 60;
    long seconds = elapsedSeconds % 60;

    std::cout << std::setfill('0') << std::setw(2) << minutes << ":"
              << std::setfill('0') << std::setw(2) << seconds;
    
    std::cout << std::flush;
}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    size_t totalSize = size * nmemb;
    str_t* response = static_cast<str_t*>(userp);
    response->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

strlist_t parseAlbumTracks(const str_t& rawJsonResponse) {
    strlist_t trackIds;

    try {
        auto parsedJson = json::parse(rawJsonResponse);
        
        if (parsedJson.contains("data") && 
            parsedJson["data"].contains("albumUnion") && 
            parsedJson["data"]["albumUnion"].contains("tracksV2") &&
            parsedJson["data"]["albumUnion"]["tracksV2"].contains("items")) {
            
            auto items = parsedJson["data"]["albumUnion"]["tracksV2"]["items"];

            for (const auto& item : items) {
                if(item.contains("track") && item["track"].contains("uri")) {
                    str_t fullUri = item["track"]["uri"];
                    trackIds.push_back(fullUri);
                }
            }
        } else {
            std::cerr << "[WARN] Unknown AlbumTracks structure or error: " << rawJsonResponse << std::endl;
        }
    } catch(json::parse_error& e) {
        std::cerr << "Parse-Error in parseAlbumTracks: " << e.what() << std::endl;
    }

    return trackIds;
}

strlist_t makeTrackIdUnique(const strlist_t& trackIds) {
    if(allowDuplicates) return trackIds;
    strlist_t uniqueIds = trackIds;
    std::sort(uniqueIds.begin(), uniqueIds.end());
    auto ip = std::unique(uniqueIds.begin(), uniqueIds.end());
    uniqueIds.erase(ip, uniqueIds.end());
    return uniqueIds;
}

str_t sendPostRequest(json& payload) {
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if(!curl) return "";
    str_t path = "config.yaml";
    YAML::Node conf = loadYaml(path);

    str_t response;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(500, 1500);
    std::this_thread::sleep_for(std::chrono::milliseconds(distr(gen)));

    int limit = conf["render-ahead-limit"].as<int>(20);
    payload["variables"]["limit"] = limit;
    str_t body = payload.dump();

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "content-type: application/json");
    headers = curl_slist_append(headers, ("authorization: Bearer " + conf["authorization-bearer"].as<str_t>()).c_str());
    headers = curl_slist_append(headers, ("client-token: " + conf["client-token"].as<str_t>()).c_str());

    curl_easy_setopt(curl, CURLOPT_URL, "https://api-partner.spotify.com/pathfinder/v2/query");
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, body.size());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    res = curl_easy_perform(curl);

    if(res != CURLE_OK) {
        std::cerr << "curl failed: " << curl_easy_strerror(res) << std::endl;
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    return response;
}

strlist_t getArtistDiscography(void) {
    strlist_t discographyUris;

    str_t opName = "queryArtistDiscographyAll";
    str_t path = "config.yaml";

    YAML::Node conf = loadYaml(path);

    json payload = json::object();
    payload["operationName"] = opName;

    strlist_t artists = conf["artists"].as<strlist_t>();

    for (str_t& artist : artists) {
        json variables = json::object();
        variables["limit"] = 20;
        variables["offset"] = 0;
        variables["order"] = "DATE_DESC";
        variables["uri"] = "spotify:artist:" + searchSuggestions(artist);
        payload["variables"] = variables;

        json extensions = json::object();
        json persistedQuery = json::object();
        persistedQuery["sha256Hash"] = "5e07d323febb57b4a56a42abbf781490e58764aa45feb6e3dc0591564fc56599";
        persistedQuery["version"] = 1;
        extensions["persistedQuery"] = persistedQuery;
        payload["extensions"] = extensions;

        str_t body = payload.dump();
        str_t response = sendPostRequest(payload);

        long http_code = 0;
        if(isDebug) {
            std::cout << "[DEBUG Artist] HTTP Status Code: " << http_code << std::endl;
            std::cout << "[DEBUG Artist] Response length: " << response.length() << " Bytes" << std::endl;
        }
            
        if (response.empty()) {
            if(isDebug) {
                std::cout << "[DEBUG Artist] Sent Payload was: " << body << "\n\n";
            }
            return discographyUris;
        }

        try {
            auto parsedJson = json::parse(response);
            
            if (parsedJson.contains("data") && 
                parsedJson["data"].contains("artistUnion") && 
                parsedJson["data"]["artistUnion"].contains("discography") &&
                parsedJson["data"]["artistUnion"]["discography"].contains("all") &&
                parsedJson["data"]["artistUnion"]["discography"]["all"].contains("items")) {
                
                auto items = parsedJson["data"]["artistUnion"]["discography"]["all"]["items"];

                for (const auto& item : items) {
                    if (item.contains("releases") && item["releases"].contains("items")) {
                        auto releaseItems = item["releases"]["items"];  
                        for (const auto& release : releaseItems) {
                            if (release.contains("uri")) {
                                discographyUris.push_back(release["uri"]);
                                if(isDebug) {
                                    std::cout << "Extracted URI: " << release["uri"] <<std::endl;
                                }
                            }
                        }
                    }
                }
            } else {
                std::cerr << "[ERROR] Server responded with error response: " << response << std::endl;
                continue;
            }
        } catch (json::parse_error& e) {
            std::cerr << "Experienced error parsing discography json: " << e.what() << std::endl;
            continue;
        }
    }

    return discographyUris;
}

int getAlbumNameAndTracks(void) {
    strlist_t trackUris;
    strlist_t discographyUris = getArtistDiscography();

    if (discographyUris.empty()) {
        std::cerr << "[ABORT] No Album-URIs found. Aborting." << std::endl;
        return -1;
    }

    str_t opName = "getAlbumNameAndTracks"; 

    size_t totalAlbums = discographyUris.size();
    size_t currentAlbums = 0;

    auto startTime = std::chrono::steady_clock::now();

    if(!isDebug) {
        printProgressBar(currentAlbums, totalAlbums, startTime);
    }

    for(const str_t& uri : discographyUris) {
        json payload = json::object();
        payload["operationName"] = opName;

        json variables = json::object();
        variables["limit"] = 20;
        variables["offset"] = 0;
        variables["order"] = "DATE_DESC";
        variables["uri"] = uri;
        payload["variables"] = variables;

        json extensions = json::object();
        json persistedQuery = json::object();
        persistedQuery["sha256Hash"] = "8628ad33de3267d7bef516c76a746979a5f98891a2c9eaff3dfec828abdcd983";
        persistedQuery["version"] = 1;
        extensions["persistedQuery"] = persistedQuery;
        payload["extensions"] = extensions;

        str_t response = sendPostRequest(payload);

        if(response.empty()) { currentAlbums++; continue; } else 
        {
            for(const str_t& item : parseAlbumTracks(response)) {
                trackUris.push_back(item);
            }
        }

        currentAlbums++;
        if(!isDebug) {
            printProgressBar(currentAlbums, totalAlbums, startTime);
        }
    }

    trackUris = makeTrackIdUnique(trackUris);
    return addToPlaylist(trackUris);
}

int addToPlaylist(strlist_t& trackIds) {
    if (trackIds.empty()) {
        std::cerr << "\n[ABORT] No tracks to add given!" << std::endl;
        return -1;
    }

    str_t opName = "addToPlaylist";
    str_t path = "config.yaml";

    const size_t CHUNK_SIZE = 100;
    size_t totalTracks = trackIds.size();
    auto startTime = std::chrono::steady_clock::now();

    std::cout << "\nAdding " << totalTracks << " tracks to playlist..." << std::endl;

    YAML::Node conf = loadYaml(path);

    if(!allowChunking) {
        for(size_t i = 0; i < totalTracks; i += CHUNK_SIZE) {
            auto startIt = trackIds.begin() + i;
            auto endIt = trackIds.begin() + std::min(i + CHUNK_SIZE, totalTracks);

            strlist_t chunk(startIt, endIt);

            chunk = makeTrackIdUnique(chunk);

            json payload = json::object();
            payload["operationName"] = opName;

            json variables = json::object();
            
            json newPosition = json::object();
            newPosition["fromUid"] = nullptr;
            newPosition["moveType"] = "BOTTOM_OF_PLAYLIST";
            
            variables["newPosition"] = newPosition;
            variables["playlistItemUris"] = chunk;
            variables["playlistUri"] = "spotify:playlist:" + conf["playlist-to-add-to"].as<str_t>();
            payload["variables"] = variables;

            json extensions = json::object();
            json persistedQuery = json::object();
            persistedQuery["sha256Hash"] = "47b2a1234b17748d332dd0431534f22450e9ecbb3d5ddcdacbd83368636a0990";
            persistedQuery["version"] = 1;
            extensions["persistedQuery"] = persistedQuery;
            payload["extensions"] = extensions;

            str_t response = sendPostRequest(payload);
            
            if(!isDebug) {
                printProgressBar(std::min(i + CHUNK_SIZE, totalTracks), totalTracks, startTime);
            }

            if(response.empty()) {
                std::cout << "\n[ERR] Received empty response..." << std::endl;
                continue;
            }
        }
    } else { 
        trackIds = makeTrackIdUnique(trackIds);

        json payload = json::object();
        payload["operationName"] = opName;

        json variables = json::object();
        
        json newPosition = json::object();
        newPosition["fromUid"] = nullptr;
        newPosition["moveType"] = "BOTTOM_OF_PLAYLIST";
        
        variables["newPosition"] = newPosition;
        variables["playlistItemUris"] = trackIds;
        variables["playlistUri"] = "spotify:playlist:" + conf["playlist-to-add-to"].as<str_t>();
        payload["variables"] = variables;

        json extensions = json::object();
        json persistedQuery = json::object();
        persistedQuery["sha256Hash"] = "47b2a1234b17748d332dd0431534f22450e9ecbb3d5ddcdacbd83368636a0990";
        persistedQuery["version"] = 1;
        extensions["persistedQuery"] = persistedQuery;
        payload["extensions"] = extensions;

        str_t response = sendPostRequest(payload);

        if(response.empty()) {
            std::cout << "\n[ERR] Received empty response..." << std::endl;
        }
    }

    std::cout << "\nSuccessfully added all tracks to the playlist." << std::endl;

    return 0;
}

size_t levenshteins_distance(const str_t& s1, const str_t& s2) {
    const size_t len1 = s1.size();
    const size_t len2 = s2.size();

    if(len1 > len2) return levenshteins_distance(s2, s1);

    std::vector<size_t> prev_row(len1 + 1);
    std::vector<size_t> curr_row(len1 + 1);

    for(size_t i = 0; i <= len1; ++i) prev_row[i] = i;

    for(size_t j = 1; j <= len2; ++j) {
        curr_row[0] = j;
        for(size_t i = 1; i <= len1; ++i) {
            size_t cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
            curr_row[i] = std::min({
                curr_row[i - 1] + 1,
                prev_row[i] + 1,
                prev_row[i - 1] + cost,
            });
        }
        std::swap(prev_row, curr_row);
    }

    return prev_row[len1];
}

bool compareArtistName(const str_t& s1, const str_t& s2, double threshold = 0.90) {
    if(s1.empty() && s2.empty()) return true;

    size_t max_len = std::max(s1.size(), s2.size());
    size_t dist = levenshteins_distance(s1, s2);

    double similarity = 1.0 - (static_cast<double>(dist) / max_len);
    return similarity >= threshold;
}

str_t searchSuggestions(const str_t& artistName) {
    std::regex pattern("^[a-zA-Z0-9]{22}$");
    std::smatch match;

    if(std::regex_search(artistName, match, pattern)) {
        return artistName;
    }

    str_t operationName = "searchSuggestions";
    auto payload = json::object();

    payload["operationName"] = operationName;
    json variables = json::object();
    variables["includeAlbumPreReleases"] = false;
    variables["includeAuthors"] = true;
    variables["includeEpisodeContentRatingsV2"] = true;
    variables["limit"] = 50;
    variables["numberOfTopResults"] = 50;
    variables["offset"] = 0;
    variables["query"] = artistName;
    payload["variables"] = variables;

    json extensions = json::object();
    json persistedQuery = json::object();
    persistedQuery["sha256Hash"] = "556f5a15b2fdd3a7113ffd377ad9805e38a3a27b8bb1ca7d6d76bad54aa8ee12";
    persistedQuery["version"] = 1;
    extensions["persistedQuery"] = persistedQuery;
    payload["extensions"] = extensions;
    // iterate through each individual artist by querying a limit of 50, loop through all 50 of them, if artist continue on to see if the name of the artist is 90% <= typedNAme in the config file for name parsing, else continue to use URI's if no name but URI is specified.

    str_t getArtists = sendPostRequest(payload);
    try {
        auto jsonConv = json::parse(getArtists);
        //strlist_t items = jsonConv["data"]["searchV2"]["topResultsV2"];
        if(jsonConv.contains("data") && jsonConv["data"].contains("searchV2") && jsonConv["data"]["searchV2"].contains("topResultsV2") && jsonConv["data"]["searchV2"]["topResultsV2"].contains("itemsV2")) {
            auto items = jsonConv["data"]["searchV2"]["topResultsV2"]["itemsV2"];

            for(const auto& item : items) {
                if(item.contains("item") && item["item"].contains("data") && item["item"]["data"].contains("uri") && item["item"]["data"].contains("profile") && item["item"]["data"]["profile"].contains("name")) {
                    str_t URI = static_cast<str_t>(item["item"]["data"]["uri"]);
                    str_t user = static_cast<str_t>(item["item"]["data"]["profile"]["name"]);

                    if(compareArtistName(artistName, user)) {
                        if(URI.find("spotify:artist:") != std::string::npos) {
                            URI = URI.substr(15);
                            return URI;
                        }
                    }
                }
            }
        } else {
            std::cerr << "Error in searchSuggestions() REQUEST VALUE PURE: " << getArtists << std::endl;
        }
    } catch(json::exception& e) {
        std::cerr << "Error in JSON parsing: " << e.what() << std::endl;
        return "";
    }
    return "";
}

void printMessage(const str_t& message) {
    std::cout << message << std::endl;
}

void printHelp(void) {
    printMessage("=== Command Line Arguments ===");
    printMessage("--debug            | -D  || Allows for AddiFy to print debugging messages. Useful when trying to find an error.");
    printMessage("--allow-duplicates | -aD || Does not prevent duplicated songs from being added.");
    printMessage("--no-chunking      | -nC || Does not split the song list into parts of 100 songs, but sends every song in a list.");
    printMessage("--help             | -h  || Print this message.");
    return;
}

int main(int argc, char *argv[]) {
    if(!launchedMenu) {
        menu();
        launchedMenu = true;
    }

    for(int i = 1; i < argc; ++i) {
        std::string_view arg(argv[i]);

        if(arg == "--debug" || arg == "-D") {
            isDebug = true;
        }
        if(arg == "--allow-duplicates" || arg == "-aD") {
            allowDuplicates = true;
        }
        if(arg == "--no-chunking" || arg == "-nC") {
            allowChunking = false;
        }
        if(arg == "--help" || arg == "-h") {
            printHelp();
            return 0;
        }
    }

    return getAlbumNameAndTracks();
}