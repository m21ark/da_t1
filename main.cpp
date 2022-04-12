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
    Menu::start();

    return 0;
}
