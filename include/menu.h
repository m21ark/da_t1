#ifndef DA_T1_MENU_H
#define DA_T1_MENU_H

#include <iostream>
#include <fstream>
#include <chrono>
#include "../include/OptimizeProfit.h"
#include "../include/read_files.h"
#include "../include/express_deliveries.h"
#include "../include/OptimizeNumberOfDeliveries.h"

#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif

using namespace std;

/**
 * Removes empty spaces from the start and end of a string
 * @param str string to be trimmed
 * @return trimmed string
 */
string trimStr(string str);


/**
 * Tests if IOstream buffer is empty
 * @param ios buffer to be tested
 * @return boolean if buffer is empty
 */
bool emptyStream(istream &ios);

char askChar();


class Menu {
public:
    static void start();

private:

    static pair<string, string> askFiles(bool scene3 = false);

    static void scenario1(const pair<string, string> &files);

    static void scenario2(const pair<string, string> &files);

    static void scenario3(const string &file);
};


#endif //DA_T1_MENU_H
