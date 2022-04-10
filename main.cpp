<<<<<<< HEAD
#include <iostream>
#include "include/read_files.h"
#include "include/knapsack.h"
#include "include/cen3.h"
#include "include/OptimizeProfit.h"

#include <chrono>
using namespace std::chrono;
=======
#include "include/menu.h"
>>>>>>> 26a2f77fd3f7a58537750e2bbaf964782a0a272a

using namespace std;

int main() {
<<<<<<< HEAD
    // cen3();
    OptimizeProfit::greedyTrucksAndLinearKnapsack("../data/encomendas.txt", "../data/carrinhas.txt");
    OptimizeProfit::greedyTrucksAndFractionalKnapsack("../data/encomendas.txt", "../data/carrinhas.txt");

=======
    Menu::start();
>>>>>>> 26a2f77fd3f7a58537750e2bbaf964782a0a272a
    return 0;
}
