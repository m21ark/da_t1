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
    static int recursiveBruteForce(vector<Truck> trucks, vector<Order> orders);

public:
    static int greedyTrucksAndKnapsack(const std::string & del, const std::string& trucks);
    static int bruteForce(const std::string & del, const std::string& trucks);
};

#endif //DA_T1_OPTIMIZENUMBEROFDELIVERIES_H
