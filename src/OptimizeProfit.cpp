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


#define DO_HEADER     do { \
auto itTruckChosen = trucks.end(); \
int max_prof = INT32_MIN; \


void OptimizeProfit::addDayBefore(vector<Order> &v, Memento &memento) {
    State state = memento.loadDayBefore();
    for (auto &order: state.orders)
        v.push_back(order);
}

void OptimizeProfit::printProfits(const vector<int> &profits) {
    int total_profit = 0;
    for (const int &pr: profits)
        total_profit += pr;

    Timer::stop();
    cout << "Total Profit = " << total_profit << "€\n";
    cout << "Time Taken: " << Timer::getTime() << "s\n";
}

int OptimizeProfit::chooseTruckProfit(int &max_prof, vector<int> &profit, vector<Order> &orders, Memento &memento,
                                      vector<Truck> &trucks, vector<Truck>::iterator &itTruckChosen,
                                      vector<Order> &used_items, unsigned &i) {
    if (max_prof <= 0)
        return 0;
    profit.push_back(max_prof);

    memento.save({used_items, itTruckChosen->id, max_prof});
    cout << "Truck_id: " << itTruckChosen->id << endl;

    if (itTruckChosen != trucks.end())
        trucks.erase(itTruckChosen);

    for (auto e: used_items) {
        auto it = std::find(orders.begin(), orders.end(), e);
        if (it != orders.end())
            orders.erase(it);
    }

    i -= used_items.size();

    cout << (int) i << " " << used_items.size() << " " << orders.size() << " " << max_prof << " " << trucks.size()
         << endl;

    return 1;
}

// TODO BUG: The 3 functions do not print anything useful for the smaller cases (5, 10 trucks and orders)
void OptimizeProfit::greedyTrucksAndLinearKnapsack(vector<Truck> trucks, vector<Order> orders) {

    HEADER
    Knapsack knapsack(orders, 400, 400); //TODO why fixed value? ... Ricardo: It's not suppose to be
    DO_HEADER

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
}

void OptimizeProfit::greedyTrucksAndFractionalKnapsack(vector<Truck> trucks, vector<Order> orders) {

    HEADER
    Knapsack knapsack1(orders);
    DO_HEADER

        for (auto truck = trucks.begin(); truck != trucks.end(); truck++) {
            vector<Order> uI;
            int prof = ((int) knapsack1.fractionalKnapsack(uI, truck->pesoMax, truck->volMax) - truck->cost);
            if (prof > max_prof) {
                max_prof = prof;
                itTruckChosen = truck;
                used_items = uI;
            }
        }

    FOOTER
}

void OptimizeProfit::greedyTrucksAndOptimizedSpaceOfLK(vector<Truck> trucks, vector<Order> orders) {

    HEADER
    sort(trucks.begin(), trucks.end(), [](const Truck &l, const Truck &r) {
        return (double) l.cost / (double) (l.pesoMax + l.volMax) < (double) r.cost / (double) (r.pesoMax + r.volMax);
    });

    auto sorter = [](const Order &l, const Order &r) {
        return (double) l.reward / (double) (l.weight + l.volume) < (double) r.reward / (double) (l.weight + r.volume);
    };

    sort(orders.begin(), orders.end(), sorter);

    Knapsack knapsack(orders, 400, 400, false); //TODO why fixed value? ... Ricardo: It's not suppose to
    DO_HEADER

        auto f = Knapsack::getMax(trucks);
        auto d = knapsack.optimal_cost(orders, f.first, f.second);

        for (auto truck = trucks.begin(); truck != trucks.end(); truck++) {

            int prof = d[truck->pesoMax][truck->volMax].first - truck->cost;
            if (prof > max_prof) {
                max_prof = prof;
                itTruckChosen = truck;

                auto items = knapsack.knapsack_hirschberg(orders, truck->pesoMax, truck->volMax);
                vector<Order> truckOrder;
                truckOrder.reserve(items.size());
                for (auto c: items)
                    truckOrder.push_back(orders[c]);

                used_items = truckOrder;
            }
        }

    FOOTER
}





