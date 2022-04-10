#include <iostream>
#include "include/read_files.h"
#include "include/knapsack.h"
#include "include/cen3.h"
#include "include/OptmizeProfit.h"

#include <chrono>
using namespace std::chrono;

using namespace std;

int main() {
    // cen3();
    OptmizeProfit::greedyTrucksAndLinearKnapsack("../data/encomendas.txt","../data/carrinhas.txt");
    OptmizeProfit::greedyTrucksAndFractionalKnapsack("../data/encomendas.txt","../data/carrinhas.txt");

    return 0;
}
