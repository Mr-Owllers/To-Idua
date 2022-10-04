#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include "config.hpp"
#include "COLOUR.hpp"
#include <time.h>
#include <fstream>
using json = nlohmann::json;

const std::string date() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       date[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(date, sizeof(date), "%Y-%m-%d %I:%M %p", &tstruct);

    return date;
}


int main(int argc, char** argv) {
    if (argc > 1){
        if (std::string(argv[1]) == "help"){
            std::cout << BBLU "To-Idua:\n" << RESET
            << "help - shows this page\nlist - lists your ideas\nadd \"name\" \"note\" - adds an idea\nremove <id> - removes an idea\nstatus <id> \"open\" || \"in progress\" || \"done\" - changes status of an idea"
            << std::endl;
            std::cout << BBLU << "\nExamples:\n" << RESET <<"toidua list\ntoidua add \"This is an idea\" \"Idea description\"\ntoidua remove 11\ntoidua status 11 \"done\" " << std::endl;
        }
        else if (std::string(argv[1]) == "list"){
            // check if file exists
            if (FILE_EXISTS(PATH)){
                std::ifstream i(PATH);
                json j;
                i >> j;
                // check if j["ideas"] is empty
                if (j["ideas"].empty()){
                    std::cout << BRED << "You have not made any ideas yet" << RESET << std::endl;
                }
                else {
                    std::cout << BBLU << "Ideas:" << RESET << std::endl;
                    for (auto& element : j["ideas"]) {
                        std::cout << element["id"] << " - " << element["idea"] << std::endl;
                        if (element["status"] == "done"){
                            std::cout << BBLU << "+" << RESET << "  Status: " << BGRN << "DONE" << RESET << std::endl;
                        }
                        else if (element["status"] == "in progress"){
                            std::cout << BBLU << "+" << RESET << "  Status: " << BYEL << "IN PROGRESS" << RESET << std::endl;
                        }
                        else if (element["status"] == "open"){
                            std::cout << BBLU << "+" << RESET << "  Status: " << BRED << "OPEN" << RESET << std::endl;
                        }
                        std::cout << BBLU << "+" << RESET << "  Note: " << element["description"] << std::endl;
                        std::cout << BBLU << "+" << RESET << "  Date: " << element["date"] << std::endl;
                    }
                }
            }
            else {
                std::cout << BRED << PATH << " does not exist. add an idea to create it" << RESET << std::endl;
            }
        }
        else if (std::string(argv[1]) == "path"){
            std::cout << PATH << std::endl;
        }
        // check if argv[1] = "add" then add argv[2] as idea to file and rest in qoutes as description
        else if (std::string(argv[1]) == "add"){
            // check if argv[2] is empty
            if (argv[2] == NULL){
                std::cout << BRED << "Please enter an idea" << RESET << std::endl;
            }
            else {
                // check if argv[3] is empty
                if (argv[3] == NULL){
                    std::cout << BRED "Please enter a description" << RESET << std::endl;
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
                            {"date", date()},
                            {"status", "open"},
                            {"id", idea["ideas"].size()}
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
                                {"date", date()},
                                {"status", "open"},
                                {"id", 0}
                            }
                        };
                        out << std::setw(4) << idea << std::endl;
                    }
                }
            }
        }
        // check if argv[1] = "remove" then remove the index that matches argv[2]
        else if (std::string(argv[1]) == "remove"){
            // check if argv[2] is empty
            if (argv[2] == NULL){
                std::cout << BRED << "Please enter an idea id" << RESET << std::endl;
            }
            else {
                // check if index is a number
                if (std::string(argv[2]).find_first_not_of("0123456789") == std::string::npos){
                    if (FILE_EXISTS(PATH)){
                        // read file
                        std::ifstream read(PATH);
                        json idea;
                        read >> idea;
                        // check if index exists in file
                        if (std::stoi(argv[2]) < idea["ideas"].size()){
                            // remove idea
                            idea["ideas"].erase(idea["ideas"].begin() + std::stoi(argv[2]));
                            // update ids of ideas
                            for (int i = 0; i < idea["ideas"].size(); i++){
                                idea["ideas"][i]["id"] = i;
                            }
                            // write file
                            std::ofstream out(PATH);
                            out << std::setw(4) << idea << std::endl;
                        }
                        else {
                            std::cout << BRED << "Index does not exist" << RESET << std::endl;
                        }
                    }
                    else {
                        std::cout << BRED << "File does not exist" << RESET << std::endl;
                    }
                }
                else {
                    std::cout << BRED << "Please enter a number" << RESET << std::endl;
                }
            }
        }
        // check if argv[1] = "status" then change the status of the index that matches argv[2] to argv[3]
        else if (std::string(argv[1]) == "status"){
            // check if argv[2] is empty
            if (argv[2] == NULL){
                std::cout << BRED << "Please enter an idea id" << RESET << std::endl;
            }
            else {
                // check if argv[3] is empty
                if (argv[3] == NULL){
                    std::cout << BRED << "Please enter a status" << RESET << std::endl;
                }
                else {
                    // check if index is a number
                    if (std::string(argv[2]).find_first_not_of("0123456789") == std::string::npos){
                        if (FILE_EXISTS(PATH)){
                            // read file
                            std::ifstream read(PATH);
                            json idea;
                            read >> idea;
                            // check if index exists in file
                            if (std::stoi(argv[2]) < idea["ideas"].size()){
                                // change status
                                // if argv[3] != "done" || "in progress" || "open" then throw error
                                if (std::string(argv[3]) == "done" || std::string(argv[3]) == "in progress" || std::string(argv[3]) == "open"){
                                    idea["ideas"][std::stoi(argv[2])]["status"] = argv[3];
                                    // write file
                                    std::ofstream out(PATH);
                                    out << std::setw(4) << idea << std::endl;
                                }
                                else {
                                    std::cout << BRED << "Please enter a valid status" << RESET << std::endl;
                                }
                            }
                            else {
                                std::cout << BRED << "Index does not exist" << RESET << std::endl;
                            }
                        }
                        else {
                            std::cout << BRED << "File does not exist" << RESET << std::endl;
                        }
                    }
                    else {
                        std::cout << BRED << "Please enter a number" << RESET << std::endl;
                    }
                }
            }
        }
        else {
            std::cout << BRED << "3RR0R 404:Command Not Found. Use \"toidua help\" for help" << RESET << std::endl;
        }
    }
    if (argc == 1){
        std::cout << BRED << "Please enter \"toidua help\" for help" << RESET << std::endl;
    }
    return 0;
}