#ifndef DA_T1_OPTIMIZENUMBEROFDELIVERIES_H
#define DA_T1_OPTIMIZENUMBEROFDELIVERIES_H

#include <vector>
#include <string>
#include <map>
#include <set>
#include "Objects.h"
#include "knapsack.h"

using namespace std;

class OptimizeNumberOfDeliveries {
    static int getMaxVolumeTrucks(vector<Truck>& trucks);
    static int getMaxWeightTrucks(vector<Truck>& trucks);
    static int getNumberOfDeliveries(Truck truck, vector<Order*>& combination);
    static void getAllDeliveriesCombinations(unsigned int depth, vector<Order>& orders, vector<vector<Order*>>& combinations);
    static int countTrucksUsedBackTracking(map<Truck, set<Order*>>& deliveries);
    static bool truckCanStillCarry(Truck truck, set<Order*>& orders,  Order* newOrder);
    static int backtrackingRec(map<Truck, set<Order*>>& deliveries, vector<Order*> unselectedOrders, int& numberOfOrders);


public:
    static void greedyTrucksAndKnapsack(const std::string & del, const std::string& trucks);
    static void greedyTrucksAndBruteForce(const std::string & del, const std::string& trucks);
    static void backtracking(const std::string & del, const std::string& trucks);
    /*
     * Backtracking
     * Ter a lista de trucks e experimentando adicionar uma order a cada um deles e retroceder quando n funcionar
     * Talvez se possa implementar threads
     */
};

#endif //DA_T1_OPTIMIZENUMBEROFDELIVERIES_H
