#ifndef DA_T1_MENU_H
#define DA_T1_MENU_H

#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <algorithm>
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

/**
 * Asks user for a char
 * @return user given char
 */
char askChar();

/**
 * Simple Menu Terminal GUI
 * prompting user to choose one of the 3 scenarios
 */
class Menu {
public:
    /**
     * Starts the Menu Terminal GUI
     */
    static void start();

private:
    /**
     * Asks user for the Truck and Order files used as input for the scenarios
     * @param scene3 boolean if scenario 3 was chosen
     * @return string pair for the user provided file paths
     */
    static pair<string, string> askFiles(bool scene3 = false);

    /**
     * Invokes scenario 1 algorithms menu
     * @param files file paths to be used as input for the algorithms
     */
    static void scenario1(const pair<string, string> &files);

    /**
     * Invokes scenario 2 algorithms menu
     * @param files file paths to be used as input for the algorithms
     */
    static void scenario2(const pair<string, string> &files);

    /**
     * Invokes scenario 3 algorithms menu
     * @param files file path to be used as input for the algorithms
     */
    static void scenario3(const string &file);
};


#endif //DA_T1_MENU_H
