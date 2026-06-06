#include "../Include/menu.h"
#include "../Include/typedefs.h"
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <yaml-cpp/node/node.h>

void print(const str_t& string);
int menu(void);
void confCurRam(void);
str_t userChoice;
str_t fP;
int userNum;

void print(const str_t& string) {
    std::cout << string << std::endl;
    return;
} 

int menu(void) {
    while(true) {
        print("        --==  AddiFy  CLI  GUI  ==--        ");
        print("");
        print("  → [1] Load YAML file from custom path     ");
        print("  → [2] Load temporary YAML file in RAM     ");
        print("  → [3] Configure current selected YAML file");
        print("");
        print("  → [4] Run AddiFy with current config      ");
        print("");
        std::cout << "    [1, 2, 3, 4] → ";
        std::cin >> userChoice;
        std::cout << std::endl;

        try {
            userNum = std::stoi(userChoice);
        } catch(const std::invalid_argument& e) {
            print("Not an integer.");
            continue;
        } catch(const std::out_of_range& e) {
            print("Out of range integer.");
            continue;
        } catch(const std::exception& e) {
            print("An unknown exception occured. If you haven't done any stupid bogus stuff, please open a github issue with the following error message:");
            print("=== BEGIN  LOG ===");
            print(e.what());
            print("=== END OF LOG ===");
            return 1;
        }

        if(userNum == 1) {
            std::cout << "Please enter the yaml's ABSOLUTE file path: ";
            std::cin >> fP;
            if(std::filesystem::exists(fP)) {
                YAML::Node conf = loadYaml(fP);
                if(!conf.IsNull() && conf.IsDefined()) {
                    print("File valid!");
                    continue;
                } else {
                    print("File invalid! Retrying with RAM option.");
                    continue;
                }
            }
        } else if(userNum == 2) {
            print("Loading RAMYAML()");
            RAMYAML();
            continue;
        } else if(userNum == 3) {
            confCurRam();
            continue;
        } else if(userNum == 4) {
            break;
        } else {
            print("Invalid option passed.");
            continue;
        }
    }
    return 0;
}

void confCurRam(void) {
    if(fP.empty()) {
        fP = "config.yaml";
    }

    if(!std::filesystem::exists(fP)) {
        std::ofstream newFile(fP);
        newFile.close();
    }

    const char *editor = std::getenv("EDITOR");
    if(!editor) editor = "nano";

    str_t cmd = str_t(editor) + " " + fP;
    std::system(cmd.c_str());

    try{
        YAML::LoadFile(fP);

        return;
    } catch(YAML::Exception e) {
        std::cerr << "YAML Encountered a parsing error: " << e.what() << std::endl;
        return;
    }
    return;
}