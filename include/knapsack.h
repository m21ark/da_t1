#ifndef DA_T1_KNAPSACK_H
#define DA_T1_KNAPSACK_H


#include "read_files.h"
#include "algorithm"


class Knapsack {

private:
    vector<Order>& store;
    vector<vector<vector<size_t>>> T;
    size_t W{} ;
    size_t Vo{};
    size_t n;
public:
    explicit Knapsack(vector<Order> &store, const size_t WeightCapacity, const size_t VolumeCapacity) : store(store){
        this->W = WeightCapacity;
        this->Vo = VolumeCapacity;
        n = store.size();
        T = vector<vector<vector<size_t>>>(n + 1, vector<vector<size_t>>(W +1, vector<size_t>(Vo +1)));

    }
    explicit Knapsack(vector<Order> &store) : store(store){
        n = store.size();
    }
    size_t knapsack_2d();
    size_t get_best_value(size_t WeightCapacity, size_t VolumeCapacity);
    vector<Order*> get_used_items(size_t W, size_t Vo);
    double fractionalKnapsack(vector<Order *>& usedItems, size_t W, size_t Vo);

    void print_knapsack();
};


#endif //DA_T1_KNAPSACK_H