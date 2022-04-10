//
// Created by ricar on 10/04/2022.
//

#include "../include/OptmizeProfit.h"
#include "../include/knapsack.h"

void OptmizeProfit::greedyTrucksAndLinearKnapsack(const std::string &del, const std::string &trucks) {
    vector<Order> v = read_orders(del);

    vector<Truck> t = read_trucks(trucks);


    vector<int> profit;
    vector<Order *> used_items;
    int i = v.size();
    size_t p = 0;


    Knapsack knapsack(v,400,400);

    do {
        knapsack.knapsack_2d();

        int max_prof = INT_MIN;

        // O(n * k) ... just an access to a vector that counts k iterations at maximum being k ~ size of orders
        for (auto &truck: t) {
            int prof = ((int)knapsack.get_best_value(truck.pesoMax, truck.volMax) - truck.cost);
            if (prof > max_prof) {
                max_prof = prof;
                used_items = knapsack.get_used_items(truck.pesoMax, truck.volMax);
            }
        }
        p++;
        profit.push_back(max_prof);

        //knapsack.print_knapsack();*/
        /*
         *
         *  ATTENTION :::: PRINT MUST BE CALLED BEFORE ERASING
         *
         */

        for (auto e : used_items) {
            auto it = std::find(v.begin(), v.end(), *e);
            if ( it != v.end())
                v.erase(it);
        }

        i-=used_items.size();
        cout << i << " " << p << " " <<  used_items.size() << " " << v.size() << " " << max_prof << endl;
    } while (i > 0 && p != t.size());


    int comul_prof = 0;
    for (auto & pr: profit) {
        comul_prof += pr;
    }
    cout << "PROF = " << comul_prof <<endl;
}

void OptmizeProfit::greedyTrucksAndFractionalKnapsack(const std::string &del, const std::string &trucks) {
    vector<Order> v = read_orders(del);

    vector<Truck> t = read_trucks(trucks);
    vector<int> profit;
    vector<Order *> used_items;
    int i = v.size();
    size_t p = 0;

    Knapsack knapsack1(v);

    do {
        int max_prof = INT_MIN;
        for (auto &truck: t) {
            vector<Order *> uI;
            int prof = ((int)knapsack1.fractionalKnapsack(uI, truck.pesoMax, truck.volMax) - truck.cost);
            if (prof > max_prof) {
                max_prof = prof;
                used_items = uI;
            }
        }
        p++;
        profit.push_back(max_prof);

        for (auto e : used_items) {
            auto it = std::find(v.begin(), v.end(), *e);
            if ( it != v.end())
                v.erase(it);
        }

        i-=used_items.size();
        cout << i << " " << p << " " <<  used_items.size() << " " << v.size() << " " << max_prof << endl;
    } while (i > 0 && p != t.size());

    int comul_prof = 0;
    for (auto & pr: profit) {
        comul_prof += pr;
    }
    cout << "PROF = " << comul_prof <<endl;

}
