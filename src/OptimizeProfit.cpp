#include "../include/OptimizeProfit.h"

#define HEADER     Timer::start(); \
vector<int> profit; \
vector<Order> used_items; \
Memento memento; \
unsigned i = orders.size(); \
addDayBefore(orders, memento);     \


#define FOOTER if (!chooseTruckProfit(max_prof, profit, orders, memento, trucks, itTruckChosen, used_items, i)) \
break; \
} while (i > 0 && !trucks.empty()); \
memento.save({orders}); \
printProfits(profit);                  \


void OptimizeProfit::addDayBefore(vector<Order> &v, Memento &memento) {
    State state = memento.loadDayBefore();
    v << state.orders;
}

void OptimizeProfit::printProfits(const vector<int> &profits) {

    int total_profit = accumulate(profits.begin(), profits.end(), 0);
    if (total_profit == 0)
        cout << "It's possible that there is not a profitable option for today's deliveries.\n";
    else {
        cout << "\nTotal Profit = " << total_profit << "€\n";
        cout << "Time Taken: " << Timer::getCurrentTime() << "s\n";
    }
}

bool OptimizeProfit::chooseTruckProfit(int &max_prof, vector<int> &profit, vector<Order> &orders, Memento &memento,
                                       vector<Truck> &trucks, vector<Truck>::iterator &itTruckChosen,
                                       vector<Order> &used_items, unsigned &i) {
    if (max_prof <= 0)
        return false;
    profit.push_back(max_prof);

    memento.save({used_items, itTruckChosen->id, max_prof});

    cout << "Truck_id: " << itTruckChosen->id << endl;

    if (itTruckChosen != trucks.end())
        trucks.erase(itTruckChosen);

    for (auto e: used_items) {
        auto it = find(orders.begin(), orders.end(), e);
        if (it != orders.end())
            orders.erase(it);
    }

    i -= used_items.size();

    cout << "Items left: " << setw(6) << (int) i << "\tItems used: " << setw(6) << used_items.size()
         << "\tOrders size: " << setw(6) << orders.size()
         << "\tMax profit: " << setw(6) << max_prof << "\tTrucks size: " << setw(6) << trucks.size() << endl;


    return true;
}


void OptimizeProfit::greedyTrucksAndLinearKnapsack(vector<Truck> trucks, vector<Order> orders) {

    HEADER
    auto p = Knapsack::getMax(trucks);
    Knapsack knapsack(orders, p.first, p.second);
    int orders_size = (int) orders.size();
    do {
        auto itTruckChosen = trucks.end();
        int max_prof = (-2147483647 - 1);

        knapsack.knapsack_2d();

        // O(n * k) ... just an access to a vector that counts k iterations at maximum being k ~ size of orders
        for (auto truck = trucks.begin(); truck != trucks.end(); truck++) {
            int prof = ((int) knapsack.get_best_value(truck->pesoMax, truck->volMax) - truck->cost);
            if (prof > max_prof) {
                max_prof = prof;
                itTruckChosen = truck;
                used_items = knapsack.get_used_items(truck->pesoMax, truck->volMax);
            }
        }

    FOOTER
    cout << "Deliveries: " << orders.size() << " / " << orders_size << " ("
         << (float) orders.size() / (float) orders_size * 100 << "%)" << endl;
}

void OptimizeProfit::greedyTrucksAndFractionalKnapsack(vector<Truck> trucks, vector<Order> orders) {

    HEADER
    Knapsack knapsack1(orders);
    int orders_size = (int) orders.size();
    do {
        auto itTruckChosen = trucks.end();
        int max_prof = (-2147483647 - 1);

        for (auto truck = trucks.begin(); truck != trucks.end(); truck++) {
            vector<Order> uI;
            int prof = ((int) knapsack1.pseudoFractionalKnapsack(uI, truck->pesoMax, truck->volMax) - truck->cost);
            if (prof > max_prof) {
                max_prof = prof;
                itTruckChosen = truck;
                used_items = uI;
            }
        }

    FOOTER
    cout << "Deliveries: " << orders.size() << " / " << orders_size << " ("
         << (float) orders.size() / (float) orders_size * 100 << "%)" << endl;

}

void OptimizeProfit::greedyTrucksAndOptimizedSpaceOfLK(vector<Truck> trucks, vector<Order> orders) {

    HEADER
    Knapsack knapsack(orders);
    int orders_size = (int) orders.size();
    do {
        auto itTruckChosen = trucks.end();
        int max_prof = (-2147483647 - 1);

        auto f = Knapsack::getMax(trucks);
        auto items = knapsack.knapsack_hirschberg(orders, f.first, f.second, max_prof, trucks);

        vector<Order> g;
        g.reserve(items.size());
        for (auto item: items) {
            g.push_back(orders[item]);
        }
        used_items = g;

        itTruckChosen = knapsack.itTruck;

    FOOTER
    cout << "Deliveries: " << orders.size() << " / " << orders_size << " ("
         << (float) orders.size() / (float) orders_size * 100 << "%)" << endl;

}





