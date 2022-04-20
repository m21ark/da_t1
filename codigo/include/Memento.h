#ifndef DA_T1_MEMENTO_H
#define DA_T1_MEMENTO_H

#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <ostream>
#include <iostream>
#include <iomanip>
#include "Objects.h"
#include "read_files.h"

#define NOT_PROVIDED -1

using namespace std;

struct State {
    vector<Order> orders;
    int truck = NOT_PROVIDED;
    int max_prof = NOT_PROVIDED;
};

class Memento {
    int year, month, day;
    struct tm now = {};
    string dir_path;

    /**
     * returns the day after x days or before
     * @param date input and output date
     * @param days the days to increment/decrement
     */
    static void datePlusDays(struct tm *date, int days) {
        const time_t ONE_DAY = 24 * 60 * 60;

        time_t date_seconds = mktime(date) + (days * ONE_DAY);

        *date = *localtime(&date_seconds);
    }

public:

    Memento() {
        time_t time = std::time(nullptr);   // get time now
        now = *localtime(&time);

        year = now.tm_year + 1900;
        month = now.tm_mon + 1;
        day = now.tm_mday;

        dir_path = "../report/" + to_string(year)
                   + to_string(month) + to_string(day);

        error_code errorCode;
        if (!filesystem::remove_all(dir_path, errorCode)) {
            cout << errorCode.message() << endl;
        }
    }

    /**
     * saves the State to a file
     * @param state
     */
    void save(const State &state);

    /**
     * saving the express orders
     * @param orders
     */
    void saveExpress(const vector<Order> &orders);

    /**
     * loads the orders from the day before
     * @return
     */
    State loadDayBefore();

};

void addDayBefore(vector<Order> &orders, Memento &memento);


#endif //DA_T1_MEMENTO_H
