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

    /**
     *  Creates a knapsack with all the needed information
     * @param store orders to be consider
     * @param WeightCapacity max weight of the knapsack
     * @param VolumeCapacity max volume of the knapsack
     */
    explicit Knapsack(vector<Order> &store, const size_t WeightCapacity, const size_t VolumeCapacity) : store(store) {
        this->W = WeightCapacity;
        this->Vo = VolumeCapacity;
        n = store.size();
        T = vector<vector<vector<size_t>>>(n + 1, vector<vector<size_t>>(W + 1, vector<size_t>(Vo + 1)));

    }

    /**
     * Creates a knapsack with all the needed information
     * @param store
     */
    explicit Knapsack(vector<Order> &store) : store(store) {
        n = store.size();
    }

    /**
     * Executes a 2d knapsack considering the max volume and weight
     * @return the best knapsack value
     */
    size_t knapsack_2d();

    /**
     * Calculates an iteration on the knapsack problem
     * @param i the stage (order in which we check the 1-0)
     * @param j the weight
     * @param k the volume
     * @param increment the increment that should be added if the order is set
     */
    void knapsack_calc(size_t i, size_t j, size_t k, int increment);

    /**
     * The best result to a max Weight and volume
     * @param WeightCapacity
     * @param VolumeCapacity
     * @return the best reward
     */
    size_t get_best_value(const size_t &WeightCapacity, const size_t &VolumeCapacity);

    /**
     * Gets the items that maximize the knapsack
     * @param weight
     * @param volume
     * @return used items
     */
    vector<Order> get_used_items(size_t weight, size_t volume);

    /**
     * A pseudo-fractional knapsack
     * @param usedItems a return value ... items used are returned here
     * @param wight
     * @param weight
     * @return the best reward
     */
    double pseudoFractionalKnapsack(vector<Order> &usedItems, size_t wight, size_t weight);

    /**
     * prints the knapsack
     */
    void print_knapsack();

    /**
     * calculates the knapsack that maximizes the number of deliveries
     */
    void knapsack_2d_number_deliveries();

    /**
     * Used items that maximizes the number of deliveries
     * @param weight
     * @param volume
     * @return
     */
    vector<Order *> get_used_items_number_deliveries(size_t weight, size_t volume);

    /**
     *
     * @return number of orders
     */
    size_t getStoreSize() { return store.size(); }

    /**
     *  Calculates the best reward for the range 0 to wCap and 0 to vCap
     * @param v the vector with the orders
     * @param wCap weight capacity
     * @param vCap volume capacity
     * @return optimal cost/reward for each pair of volume, weight
     */
    vector<vector<pair<int, int>>> optimal_cost(vector<Order> const &v, int wCap, int vCap);

    /**
     * Calculates the best knapsack using a divide an conquer algorithm
     * @param v the vector with the orders
     * @param wCap Weight capacity
     * @param vCap volume capacity
     * @param prof max profit - out values
     * @param trucks the trucks responsible for the deliveries
     * @param offset the offset of the vector
     * @param firs indicates if this is the first call to the function
     * @return
     */
    vector<int> knapsack_hirschberg(const vector<Order> &v, int wCap, int vCap, int &prof,vector<Truck> &trucks,int offset = 0, bool firs = true );

    /**
     * Checks if orders fits in trucks
     * @param t vector of trucks
     * @param v vector of orders id
     * @param o vector of orders
     * @return true if it fits false otherwise
     */
    static bool fitsInTruck(const Truck &t, const vector<int> &v, const vector<Order> &o);

    /**
     * gets the max Weight and Volume of trucks
     * @param trucks
     * @return pair with max Weight , max volume
     */
    static pair<int, int> getMax(const vector<Truck> &trucks);
};


#endif //DA_T1_KNAPSACK_H
