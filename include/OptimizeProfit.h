#ifndef DA_T1_OPTIMIZEPROFIT_H
#define DA_T1_OPTIMIZEPROFIT_H

#include <string>
#include <fstream>
#include "../include/knapsack.h"
#include "../include/Memento.h"

class OptimizeProfit {
public:
    static void greedyTrucksAndLinearKnapsack(const std::string &del, const std::string &trucks);

    static void greedyTrucksAndFractionalKnapsack(const std::string &del, const std::string &trucks);
};


#endif //DA_T1_OPTIMIZEPROFIT_H