#ifndef DA_T1_OPTIMIZENUMBEROFDELIVERIES_H
#define DA_T1_OPTIMIZENUMBEROFDELIVERIES_H

#include <vector>
#include <string>
#include "Objects.h"
#include "knapsack.h"

using namespace std;

class OptimizeNumberOfDeliveries {
    static int getMaxVolumeTrucks(vector<Truck>& trucks);
    static int getMaxWeightTrucks(vector<Truck>& trucks);
    static bool compareOrderByWeight(const Order& l, const Order& r);

public:
    static void greedyTrucksAndKnapsack(const std::string & del, const std::string& trucks);
};

#endif //DA_T1_OPTIMIZENUMBEROFDELIVERIES_H
