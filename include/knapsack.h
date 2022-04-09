#ifndef DA_T1_KNAPSACK_H
#define DA_T1_KNAPSACK_H


#include "read_files.h"

class Knapsack {

private:
    vector<Order> store;
    vector<vector<vector<size_t>>> T;
public:
    explicit Knapsack(vector<Order> &store) : store(store){}
    size_t knapsack_2d(size_t WeightCapacity, size_t VolumeCapacity);
    void print_knapsack(size_t W, size_t Vo);
};


#endif //DA_T1_KNAPSACK_H
