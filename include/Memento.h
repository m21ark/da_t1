#ifndef DA_T1_MEMENTO_H
#define DA_T1_MEMENTO_H

#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <ostream>
#include <iostream>
#include "Objects.h"
#include "read_files.h"

#define NOT_PROVIDED NULL

struct State {
    std::vector<Order> orders;
    int truck = NOT_PROVIDED;
    int max_prof = NOT_PROVIDED;
};

class Memento {
    int year;
    int month;
    int day;
    struct std::tm now;
    std::string dir_path;

    void datePlusDays( struct tm* date, int days ) {
        const time_t ONE_DAY = 24 * 60 * 60;

        time_t date_seconds = mktime( date ) + (days * ONE_DAY);

        *date = *localtime( &date_seconds );
    }

public:
    Memento() {
        std::time_t time = std::time(nullptr);   // get time now
        now = *localtime(&time);

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
    State loadDayBefore();
};


#endif //DA_T1_MEMENTO_H
