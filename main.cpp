#include <iostream>
#include "include/read_files.h"
#include "include/knapsack.h"
#include "include/cen3.h"
#include "include/OptimizeProfit.h"

#include <chrono>
using namespace std::chrono;
#include "include/menu.h"
#include "include/OptimizeNumberOfDeliveries.h"

using namespace std;

int main() {
    // cen3();
    //OptimizeProfit::greedyTrucksAndLinearKnapsack("../data/encomendas.txt", "../data/carrinhas.txt");
    //OptimizeProfit::greedyTrucksAndFractionalKnapsack("../data/encomendas.txt", "../data/carrinhas.txt");
    //OptimizeNumberOfDeliveries::greedyTrucksAndKnapsack("../data/encomendas.txt", "../data/carrinhas.txt");

    /*
    OptimizeNumberOfDeliveries::greedyTrucksAndKnapsack("../data/e_5/e_1.txt", "../data/c_1/c_extra.txt");
    OptimizeNumberOfDeliveries::greedyTrucksAndBruteForce("../data/e_5/e_1.txt", "../data/c_1/c_extra.txt");
    OptimizeNumberOfDeliveries::backtracking("../data/e_5/e_1.txt", "../data/c_1/c_extra.txt");
    */
    /*
    OptimizeNumberOfDeliveries::greedyTrucksAndKnapsack("../data/e_10/e_1.txt", "../data/c_2/cextra.txt");
    OptimizeNumberOfDeliveries::greedyTrucksAndBruteForce("../data/e_10/e_1.txt", "../data/c_2/cextra.txt");
    OptimizeNumberOfDeliveries::backtracking("../data/e_10/e_1.txt", "../data/c_2/cextra.txt");
     */
    //OptimizeNumberOfDeliveries::backtracking("../data/e_10/e_1.txt", "../data/c_5/c_1.txt");

    Menu::start();

    return 0;
}
