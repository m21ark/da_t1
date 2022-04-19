#ifndef DA_T1_OPTIMIZE_NUMBER_OF_DELIVERIES_H
#define DA_T1_OPTIMIZE_NUMBER_OF_DELIVERIES_H

#include <vector>
#include <string>
#include <map>
#include <set>
#include "Objects.h"
#include "Memento.h"
#include "knapsack.h"
#include "timer.h"

using namespace std;

class OptimizeNumberOfDeliveries {

    /**
     * Gets the maximum volume of a truck from the trucks given
     * @param trucks
     * @return max volume
     */
    static int getMaxVolumeTrucks(const vector<Truck> &trucks);

    /**
     * Gets the maximum weight of a truck from the trucks given
     * @param trucks
     * @return max weight
     */
    static int getMaxWeightTrucks(const vector<Truck> &trucks);


    /**
     * Returns the number of orders if they can fit inside the truck
     * @param truck
     * @param combination
     * @return number of orders if it fits, else returns -1
     */
    static int getNumberOfDeliveries(const Truck &truck, vector<Order *> &combination);

    /**
     * It returns by reference in combinations, all possible combinations of orders
     * @param depth
     * @param orders
     * @param combinations
     */
    static void getAllDeliveriesCombinations(const unsigned &depth, vector<Order> &orders, vector<vector<Order *>> &combinations);

    /**
     * Counts the number of trucks used (those that have at least one order)
     * @param deliveries
     * @return number of trucks
     */
    static int countTrucksUsedBackTracking(const map<Truck, set<Order *>> &deliveries);

    /**
     * It checks if the truck can still carry the new order
     * @param truck
     * @param orders
     * @param newOrder
     * @return true if it fits, false otherwise
     */
    static bool truckCanStillCarry(const Truck &truck, const set<Order *> &orders, const Order *newOrder);

    /**
     * Recursive part of the backtracking algorithm.
     * @param deliveries
     * @param unselectedOrders
     * @param numberOfOrders
     * @return number of trucks used
     */
    static int backtrackingRec(map<Truck, set<Order *>> &deliveries, vector<Order *> unselectedOrders, int &numberOfOrders);

    /**
     * Prints the results
     * @param totalDeliveries
     * @param numberOfTrucks
     */
    static void printResults(const unsigned &totalDeliveries, const unsigned &numberOfTrucks);

    /**
     * It erases the used items in ordersV
     * if print is true, it prints the orders deleted
     * @param usedItems
     * @param ordersV
     * @param print
     */
    static void eraseSavedOrders(const vector<Order> &usedItems, vector<Order> &ordersV, bool print = true);

    /**
     * Comparison function used to sort orders to be used in greedy
     * Takes into consideration both weight and volume
     * @param o1
     * @param o2
     * @return true if o1 < o2
     */
    static bool compareByWeightAndVolume(const Order& o1, const Order& o2);

    /**
     * Chooses the best orders for a certain truck in a greedy way
     * It also passes by reference the orders chosen in usedItems
     * @param truck
     * @param orders
     * @param usedItems
     * @return number of orders that the truck can carry
     */
    static unsigned getGreedyNumberOfOrdersOfTruck(Truck &truck, vector<Order>& orders, vector<Order *>& usedItems);

public:

    /**
     * One of the main functions of scenario 1
     * It calculates the distribution of deliveries in the trucks, by choosing the truck with the most amount of deliveries calculated using knapsack
     * Then it keeps chosing the truck with the most number of deliveries for the remaining orders (greedy)
     * until either there are no more orders or all trucks are full
     * @param trucksV
     * @param ordersV
     */
    static void greedyTrucksAndKnapsack(vector<Truck> trucksV, vector<Order> ordersV);

    /**
     * One of the main functions of scenario 1
     * It calculates the distribution of deliveries in the trucks, by choosing the truck with the most amount of deliveries calculated using a greedy algorithm
     * Then it keeps choosing the truck with the most number of deliveries for the remaining orders (greedy)
     * until either there are no more orders or all trucks are full
     * @param trucksV
     * @param ordersV
     */
    static void greedyTrucksAndGreedyOrders(vector<Truck> trucksV, vector<Order> ordersV);

    /**
     * One of the main functions of scenario 1
     * It calculates the distribution of deliveries in the trucks, by choosing the truck with the most amount of deliveries calculated using a brute force
     * 
     * @param trucksV
     * @param ordersV
     */
    static void greedyTrucksAndBruteForce(vector<Truck> trucksV, vector<Order> ordersV);

    static void backtracking(const vector<Truck> &trucksV, vector<Order> ordersV);

};


#endif //DA_T1_OPTIMIZE_NUMBER_OF_DELIVERIES_H
