#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include "config.hpp"
#include <ctime>
#include <fstream>
using json = nlohmann::json;

int main(int argc, char** argv) {
    if (argc > 1){
        if (std::string(argv[1]) == "help"){
            std::cout << "To-Idua\n-------------------\nhelp - shows this page\nlist - lists your ideas" << std::endl;
        }
        else if (std::string(argv[1]) == "list"){
            std::cout << "Test" << std::endl;
        }
        else if (std::string(argv[1]) == "path"){
            std::cout << PATH << std::endl;
        }
        // check if argv[1] = "add" then add argv[2] as idea to file and rest in qoutes as description
        else if (std::string(argv[1]) == "add"){
            // check if argv[2] is empty
            if (argv[2] == NULL){
                std::cout << "Please enter an idea" << std::endl;
            }
            else {
                // check if argv[3] is empty
                if (argv[3] == NULL){
                    std::cout << "Please enter a description" << std::endl;
                }
                else {
                    
                    // check if file exists
                    if (FILE_EXISTS(PATH)){
                        // read file
                        std::ifstream read(PATH);
                        json idea;
                        read >> idea;
                        // add idea
                        idea["ideas"].push_back({
                            {"idea", argv[2]},
                            {"description", argv[3]},
                            {"date", std::time(0)},
                            {"done", false}
                        });
                        // write file
                        std::ofstream out(PATH);
                        out << std::setw(4) << idea << std::endl;
                    }
                    else {
                        // create file
                        std::ofstream out(PATH);
                        json idea;
                        idea["ideas"] = {
                            {
                                {"idea", argv[2]},
                                {"description", argv[3]},
                                {"date", std::time(0)},
                                {"done", false}
                            }
                        };
                        out << std::setw(4) << idea << std::endl;
                    }
                }
            }
        }
        else {
            std::cout << "3RR0R 404:Command Not Found" << std::endl;
        }
    }
    return 0;
}