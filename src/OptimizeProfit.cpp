#include "../include/OptimizeProfit.h"

void OptimizeProfit::addDayBefore(vector<Order> &v, Memento &memento) {
    State state = memento.loadDayBefore();
    for (auto &order: state.orders)
        v.push_back(order);
}

void OptimizeProfit::greedyTrucksAndLinearKnapsack(vector<Truck> trucks, vector<Order> orders) {

    Timer::start();

    vector<int> profit;
    vector<Order> used_items;
    unsigned i = orders.size();

    Memento memento;
    addDayBefore(orders, memento);

    Knapsack knapsack(orders, 400, 400);

    do {
        knapsack.knapsack_2d();
        auto itTruckChosen = trucks.end();

        int max_prof = INT32_MIN;


        // O(n * k) ... just an access to a vector that counts k iterations at maximum being k ~ size of orders
        for (auto truck = trucks.begin(); truck != trucks.end(); truck++) {
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

        //knapsack.print_knapsack(); // PRINT MUST BE CALLED BEFORE ERASING

        memento.save({used_items, itTruckChosen->id, max_prof});
        cout << itTruckChosen->id << endl;

        if (itTruckChosen != trucks.end())
            trucks.erase(itTruckChosen);

        for (auto e: used_items) {
            auto it = std::find(orders.begin(), orders.end(), e);
            if (it != orders.end())
                orders.erase(it);
        }
        i -= used_items.size();
        cout << i << " " << used_items.size() << " " << orders.size() << " " << max_prof << " " << trucks.size()
             << endl;
    } while (i > 0 && !trucks.empty());

    memento.save({orders});

    int total_profit = 0;
    for (auto &pr: profit)
        total_profit += pr;

    Timer::stop();
    cout << "Total Profit = " << total_profit << endl;
    cout << "Time Taken: " << Timer::getTime() << endl;
}

void OptimizeProfit::greedyTrucksAndFractionalKnapsack(vector<Truck> trucks, vector<Order> orders) {

    Timer::start();

    vector<int> profit;
    vector<Order> used_items;
    Memento memento;
    Knapsack knapsack1(orders);
    addDayBefore(orders, memento);
    unsigned i = orders.size();

    do {
        auto itTruckChosen = trucks.end();

        int max_prof = INT32_MIN;

        for (auto truck = trucks.begin(); truck != trucks.end(); truck++) {
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

        if (itTruckChosen != trucks.end())
            trucks.erase(itTruckChosen);

        for (auto e: used_items) {
            auto it = std::find(orders.begin(), orders.end(), e);
            if (it != orders.end())
                orders.erase(it);
        }

        i -= used_items.size();
        cout << i << " " << used_items.size() << " " << orders.size() << " " << max_prof << " " << trucks.size()
             << endl;
    } while (i > 0 && !trucks.empty());

    memento.save({orders});

    int total_profit = 0;
    for (auto &pr: profit)
        total_profit += pr;

    Timer::stop();
    cout << "Total Profit = " << total_profit << endl;
    cout << "Time Taken: " << Timer::getTime() << endl;
}


