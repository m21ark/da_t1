//
// Created by ricar on 12/04/2022.
//

#ifndef DA_T1_MEMENTO_H
#define DA_T1_MEMENTO_H

#include <fstream>
#include <filesystem>
#include "Objects.h"
#include <string>
#include <ostream>
#include "iostream"

#define NOT_PROVIDED NULL

struct State{
    const std::vector<Order>& orders;
    int truck = NOT_PROVIDED;
    int max_prof = NOT_PROVIDED;
};

class Memento {
    int year ;
    int month;
    int day  ;
    std::string dir_path;
public:
    Memento() {
        std::time_t time = std::time(nullptr);   // get time now
        struct std::tm now = *localtime(&time);

        year = now.tm_year + 1900;
        month = now.tm_mon + 1;
        day = now.tm_mday;

        dir_path = "../report/" + std::to_string(year)
                          + std::to_string(month) + std::to_string(day);

        std::error_code errorCode;
        if (!std::filesystem::remove_all(dir_path, errorCode)) {
            std::cout << errorCode.message() << std::endl;
        }
    }

    void save(State state);
};


#endif //DA_T1_MEMENTO_H
