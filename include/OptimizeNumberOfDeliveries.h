#ifndef DA_T1_OPTIMIZE_NUMBER_OF_DELIVERIES_H
#define DA_T1_OPTIMIZE_NUMBER_OF_DELIVERIES_H

#include <vector>
#include <string>
#include <map>
#include <set>
#include "Objects.h"
#include "knapsack.h"
#include "timer.h"

using namespace std;

class OptimizeNumberOfDeliveries {
    static int getMaxVolumeTrucks(const vector<Truck> &trucks);

    static int getMaxWeightTrucks(const vector<Truck> &trucks);

    static int getNumberOfDeliveries(const Truck &truck, vector<Order *> &combination);

    static void
    getAllDeliveriesCombinations(const unsigned &depth, vector<Order> &orders, vector<vector<Order *>> &combinations);

    static int countTrucksUsedBackTracking(const map<Truck, set<Order *>> &deliveries);

    static bool truckCanStillCarry(const Truck &truck, set<Order *> &orders,const Order *newOrder);

    static int
    backtrackingRec(map<Truck, set<Order *>> &deliveries, vector<Order *> unselectedOrders, int &numberOfOrders);


public:
    static void greedyTrucksAndKnapsack(vector<Truck> trucksV, vector<Order> ordersV);

    static void greedyTrucksAndBruteForce(vector<Truck> trucksV, vector<Order> ordersV);

    static void backtracking(const vector<Truck> &trucksV, vector<Order> ordersV);

};

#endif //DA_T1_OPTIMIZE_NUMBER_OF_DELIVERIES_H
