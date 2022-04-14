#include "../include/OptimizeProfit.h"


void OptimizeProfit::greedyTrucksAndLinearKnapsack(const std::string &del, const std::string &trucks) {
    vector<Order> v = read_orders(del);

    vector<Truck> t = read_trucks(trucks);


    vector<int> profit;
    vector<Order> used_items;
    int i = v.size();

    Memento memento;
    addDayBefore(v,memento);

    Knapsack knapsack(v, 400, 400);

    do {
        knapsack.knapsack_2d();
        auto itTruckChosen = t.end();

        int max_prof = INT32_MIN;


        // O(n * k) ... just an access to a vector that counts k iterations at maximum being k ~ size of orders
        for (auto truck = t.begin(); truck != t.end(); truck++) {
            int prof = ((int) knapsack.get_best_value(truck->pesoMax, truck->volMax) - truck->cost);
            if (prof > max_prof) {
                max_prof = prof;
                used_items = knapsack.get_used_items(truck->pesoMax, truck->volMax);
                itTruckChosen = truck;
            }
        }
        if (max_prof <= 0)
            break;
        profit.push_back(max_prof);

        //knapsack.print_knapsack();*/
        /*
         *
         *  ATTENTION :::: PRINT MUST BE CALLED BEFORE ERASING
         *
         */

        memento.save({used_items, itTruckChosen->id, max_prof});
        cout << itTruckChosen->id << endl;

        if (itTruckChosen != t.end())
            t.erase(itTruckChosen);

        for (auto e: used_items) {
            auto it = std::find(v.begin(), v.end(), e);
            if (it != v.end())
                v.erase(it);
        }
        i -= used_items.size();
        cout << i << " " << used_items.size() << " " << v.size() << " " << max_prof << " " << t.size() << endl;
    } while (i > 0 && t.size() != 0);

    memento.save({v});

    int comul_prof = 0;
    for (auto &pr: profit) {
        comul_prof += pr;
    }
    cout << "PROF = " << comul_prof << endl;
}

void OptimizeProfit::greedyTrucksAndFractionalKnapsack(const std::string &del, const std::string &trucks) {
    vector<Order> v = read_orders(del);

    vector<Truck> t = read_trucks(trucks);
    vector<int> profit;
    vector<Order> used_items;
    int i = v.size();

    Memento memento;
    addDayBefore(v,memento);

    Knapsack knapsack1(v);

    do {
        auto itTruckChosen = t.end();


        int max_prof = INT32_MIN;

        for (auto truck = t.begin(); truck != t.end(); truck++)  {
            vector<Order> uI;
            int prof = ((int) knapsack1.fractionalKnapsack(uI, truck->pesoMax, truck->volMax) - truck->cost);
            if (prof > max_prof) {
                max_prof = prof;
                used_items = uI;
                itTruckChosen = truck;

            }
        }

        if (max_prof <= 0)
            break;

        profit.push_back(max_prof);

        memento.save({used_items, itTruckChosen->id, max_prof});
        cout << itTruckChosen->id << endl;


        if (itTruckChosen != t.end())
            t.erase(itTruckChosen);

        for (auto e: used_items) {
            auto it = std::find(v.begin(), v.end(), e);
            if (it != v.end())
                v.erase(it);
        }

        i -= used_items.size();
        cout << i << " " << used_items.size() << " " << v.size() << " " << max_prof << " " << t.size() << endl;
    } while (i > 0 && t.size() != 0);

    memento.save({v});

    int comul_prof = 0;
    for (auto &pr: profit) {
        comul_prof += pr;
    }
    cout << "PROF = " << comul_prof << endl;

}

void OptimizeProfit::addDayBefore(vector<Order> &v, Memento &memento) {
    State state = memento.loadDayBefore();
    for (auto & order : state.orders) {
        v.push_back(order);
    }
}
