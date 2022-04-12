#ifndef DA_T1_OPTIMIZENUMBEROFDELIVERIES_H
#define DA_T1_OPTIMIZENUMBEROFDELIVERIES_H

#include <vector>
#include <string>
#include <set>
#include "Objects.h"
#include "knapsack.h"

using namespace std;

class OptimizeNumberOfDeliveries {
    static int getMaxVolumeTrucks(vector<Truck>& trucks);
    static int getMaxWeightTrucks(vector<Truck>& trucks);
    static int recursiveBruteForce(vector<Truck> trucks, vector<Order> orders);
    static void getAllDeliveriesCombinations(unsigned int depth, vector<Order>& orders, vector<vector<Order*>>& combinations);
    static int getNumberOfDeliveries(Truck truck, vector<Order*>& combination);

public:
    static int greedyTrucksAndKnapsack(const std::string & del, const std::string& trucks);
    static int greedyTrucksAndBruteForce(const std::string & del, const std::string& trucks);
};

#endif //DA_T1_OPTIMIZENUMBEROFDELIVERIES_H
