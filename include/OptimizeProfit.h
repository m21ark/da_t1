#ifndef DA_T1_OPTIMIZE_PROFIT_H
#define DA_T1_OPTIMIZE_PROFIT_H

#include <string>
#include <fstream>
#include "../include/knapsack.h"
#include "../include/Memento.h"
#include "timer.h"

class OptimizeProfit {
private:
    static void addDayBefore(vector<Order>& v, Memento& memento);
public:
    static void greedyTrucksAndLinearKnapsack(vector<Truck> trucks, vector<Order> orders);

    static void greedyTrucksAndFractionalKnapsack(vector<Truck> trucks, vector<Order> orders);
};


#endif //DA_T1_OPTIMIZE_PROFIT_H