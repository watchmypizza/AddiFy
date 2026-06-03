#include <algorithm>
#include <cstddef>
#include <curl/curl.h>
#include <curl/easy.h>
#include <string>
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
#include <chrono>

using json = nlohmann::json;

// load yaml
YAML::Node loadYaml(std::string& path) {
    try {
        YAML::Node yamlFile = YAML::LoadFile(path);
        return yamlFile;
    } catch(YAML::Exception& e) {
        std::cerr << "Error parsing YAML file: " << e.what() << std::endl;
        return YAML::Node();
    }
}

std::vector<std::string> parseAlbumTracks(const std::string& rawJsonResponse);
int addToPlaylist(const std::vector<std::string>& trackIds);
std::vector<std::string> getArtistDiscography(void);
std::vector<std::string> makeTrackIdUnique(const std::vector<std::string>& trackIds);

bool isDebug = false;
bool allowDuplicates = false;

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
    std::string* response = static_cast<std::string*>(userp);
    response->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

std::vector<std::string> parseAlbumTracks(const std::string& rawJsonResponse) {
    std::vector<std::string> trackIds;

    try {
        auto parsedJson = json::parse(rawJsonResponse);
        
        if (parsedJson.contains("data") && 
            parsedJson["data"].contains("albumUnion") && 
            parsedJson["data"]["albumUnion"].contains("tracksV2") &&
            parsedJson["data"]["albumUnion"]["tracksV2"].contains("items")) {
            
            auto items = parsedJson["data"]["albumUnion"]["tracksV2"]["items"];

            for (const auto& item : items) {
                if(item.contains("track") && item["track"].contains("uri")) {
                    std::string fullUri = item["track"]["uri"];
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

std::vector<std::string> makeTrackIdUnique(const std::vector<std::string>& trackIds) {
    if(allowDuplicates) return trackIds;
    std::vector<std::string> uniqueIds = trackIds;
    std::sort(uniqueIds.begin(), uniqueIds.end());
    auto ip = std::unique(uniqueIds.begin(), uniqueIds.end());
    uniqueIds.erase(ip, uniqueIds.end());
    return uniqueIds;
}

std::vector<std::string> getArtistDiscography(void) {
    std::vector<std::string> discographyUris;

    std::string opName = "queryArtistDiscographyAll";
    CURL *curl;
    CURLcode res;
    std::string path = "config.yaml";

    YAML::Node conf = loadYaml(path);

    json payload = json::object();
    payload["operationName"] = opName;

    std::vector<std::string> artists = conf["artists"].as<std::vector<std::string>>();

    for (std::string& artist : artists) {
        json variables = json::object();
        variables["limit"] = 20;
        variables["offset"] = 0;
        variables["order"] = "DATE_DESC";
        variables["uri"] = "spotify:artist:" + artist;
        payload["variables"] = variables;

        json extensions = json::object();
        json persistedQuery = json::object();
        persistedQuery["sha256Hash"] = "5e07d323febb57b4a56a42abbf781490e58764aa45feb6e3dc0591564fc56599";
        persistedQuery["version"] = 1;
        extensions["persistedQuery"] = persistedQuery;
        payload["extensions"] = extensions;

        curl = curl_easy_init();
        if(!curl) return discographyUris;

        std::string body = payload.dump();
        std::string response;

        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "content-type: application/json");
        headers = curl_slist_append(headers, ("authorization: Bearer " + conf["authorization-bearer"].as<std::string>()).c_str());
        headers = curl_slist_append(headers, ("client-token: " + conf["client-token"].as<std::string>()).c_str());

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

        long http_code = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        if(isDebug) {
            std::cout << "[DEBUG Artist] HTTP Status Code: " << http_code << std::endl;
            std::cout << "[DEBUG Artist] Response length: " << response.length() << " Bytes" << std::endl;
        }
            
        if (response.empty()) {
            if(isDebug) {
                std::cout << "[DEBUG Artist] Sent Payload was: " << body << "\n\n";
            }
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
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

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    return discographyUris;
}

int getAlbumNameAndTracks(void) {
    std::vector<std::string> trackUris;
    std::vector<std::string> discographyUris = getArtistDiscography();

    if (discographyUris.empty()) {
        std::cerr << "[ABORT] No Album-URIs found. Aborting." << std::endl;
        return -1;
    }

    std::string opName = "getAlbumNameAndTracks"; 
    CURL *curl;
    CURLcode res;
    std::string path = "config.yaml";

    YAML::Node conf = loadYaml(path);

    size_t totalAlbums = discographyUris.size();
    size_t currentAlbums = 0;

    auto startTime = std::chrono::steady_clock::now();

    if(!isDebug) {
        printProgressBar(currentAlbums, totalAlbums, startTime);
    }

    for(const std::string& uri : discographyUris) {
        curl = curl_easy_init();
        if(!curl) {
            currentAlbums++;
            continue;
        };

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

        std::string body = payload.dump();
        std::string response;

        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "content-type: application/json");
        headers = curl_slist_append(headers, ("authorization: Bearer " + conf["authorization-bearer"].as<std::string>()).c_str());
        headers = curl_slist_append(headers, ("client-token: " + conf["client-token"].as<std::string>()).c_str());

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
            // nothing lol get over it
        } else {
            for(const std::string& item : parseAlbumTracks(response)) {
                trackUris.push_back(item);
            }
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);

        currentAlbums++;
        if(!isDebug) {
            printProgressBar(currentAlbums, totalAlbums, startTime);
        }
    }

    trackUris = makeTrackIdUnique(trackUris);
    return addToPlaylist(trackUris);
}

int addToPlaylist(const std::vector<std::string>& trackIds) {
    if (trackIds.empty()) {
        std::cerr << "[ABORT] Keine Tracks zum Hinzufügen übergeben!" << std::endl;
        return -1;
    }

    std::string opName = "addToPlaylist";
    CURL *curl;
    CURLcode res;
    std::string path = "config.yaml";

    YAML::Node conf = loadYaml(path);

    json payload = json::object();
    payload["operationName"] = opName;

    json variables = json::object();
    
    json newPosition = json::object();
    newPosition["fromUid"] = nullptr;
    newPosition["moveType"] = "BOTTOM_OF_PLAYLIST";
    
    variables["newPosition"] = newPosition;
    variables["playlistItemUris"] = trackIds;
    variables["playlistUri"] = "spotify:playlist:" + conf["playlist-to-add-to"].as<std::string>();
    payload["variables"] = variables;

    json extensions = json::object();
    json persistedQuery = json::object();
    persistedQuery["sha256Hash"] = "47b2a1234b17748d332dd0431534f22450e9ecbb3d5ddcdacbd83368636a0990";
    persistedQuery["version"] = 1;
    extensions["persistedQuery"] = persistedQuery;
    payload["extensions"] = extensions;

    curl = curl_easy_init();
    if(!curl) return -1;

    std::string body = payload.dump();
    std::string response;

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "content-type: application/json");
    headers = curl_slist_append(headers, ("authorization: Bearer " + conf["authorization-bearer"].as<std::string>()).c_str());
    headers = curl_slist_append(headers, ("client-token: " + conf["client-token"].as<std::string>()).c_str());

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
    } else {
        std::cout << "\n[SUCCESS] Playlist Response: " << response << std::endl;
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    return 0;
}

int main(int argc, char *argv[]) {
    for(int i = 1; i < argc; ++i) {
        std::string_view arg(argv[i]);

        if(arg == "--debug" || arg == "-D") {
            isDebug = true;
        }
        if(arg == "--allow-duplicates" || arg == "-aD") {
            allowDuplicates = true;
        }
    }

    return getAlbumNameAndTracks();
}