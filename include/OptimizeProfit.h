#ifndef DA_T1_OPTIMIZE_PROFIT_H
#define DA_T1_OPTIMIZE_PROFIT_H

#include <string>
#include <fstream>
#include <numeric>
#include "knapsack.h"
#include "Memento.h"
#include "timer.h"

class OptimizeProfit {
private:
    static void addDayBefore(vector<Order> &v, Memento &memento);

public:
    /**
     * TODO: PASS BY REFERENCE
     */
    static void greedyTrucksAndLinearKnapsack(vector<Truck> trucks, vector<Order> orders);

    static void greedyTrucksAndFractionalKnapsack(vector<Truck> trucks, vector<Order> orders);

    static void greedyTrucksAndOptimizedSpaceOfLK(vector<Truck> trucks, vector<Order> order);

    static void printProfits(const vector<int> &profits);

    static int chooseTruckProfit(int &max_prof, vector<int> &profit, vector<Order> &orders, Memento &memento,
                                 vector<Truck> &trucks, vector<Truck>::iterator &itTruckChosen,
                                 vector<Order> &used_items, unsigned &i);

};


#endif //DA_T1_OPTIMIZE_PROFIT_H