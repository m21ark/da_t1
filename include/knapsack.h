#ifndef DA_T1_KNAPSACK_H
#define DA_T1_KNAPSACK_H

#include <algorithm>
#include "read_files.h"

class Knapsack {

private:
    vector<Order> &store;
    vector<vector<vector<size_t>>> T;
    size_t W{};
    size_t Vo{};
    size_t n;

public:
    vector<Truck>::iterator itTruck;
    explicit Knapsack(vector<Order> &store, const size_t WeightCapacity, const size_t VolumeCapacity,
                      bool reserveSpace = true) : store(store) {
        this->W = WeightCapacity;
        this->Vo = VolumeCapacity;
        n = store.size();
        if (reserveSpace)
            T = vector<vector<vector<size_t>>>(n + 1, vector<vector<size_t>>(W + 1, vector<size_t>(Vo + 1)));

    }

    explicit Knapsack(vector<Order> &store) : store(store) {
        n = store.size();
    }

    size_t knapsack_2d();

    void knapsack_calc(size_t i, size_t j, size_t k, int increment);

    size_t get_best_value(const size_t &WeightCapacity, const size_t &VolumeCapacity);

    vector<Order> get_used_items(size_t weight, size_t volume);

    double fractionalKnapsack(vector<Order> &usedItems, size_t wight, size_t weight);

    void print_knapsack();

    void knapsack_2d_number_deliveries();

    vector<Order *> get_used_items_number_deliveries(size_t weight, size_t volume);

    size_t getStoreSize() { return store.size(); }

    vector<vector<pair<int, int>>> optimal_cost(vector<Order> const &v, int wCap, int vCap);

    vector<int> knapsack_hirschberg(const vector<Order> &v, int wCap, int vCap, int &prof,vector<Truck> &trucks,int offset = 0, bool firs = true );

    static bool fitsInTruck(const Truck &t, const vector<int> &v, const vector<Order> &o);

    static pair<int, int> getMax(const vector<Truck> &trucks);
};


#endif //DA_T1_KNAPSACK_H
