#include "../include/OptimizeNumberOfDeliveries.h"

int OptimizeNumberOfDeliveries::getMaxVolumeTrucks(const vector<Truck> &trucks) {
    auto func = [](const Truck &left, const Truck &right) {
        return left.volMax < right.volMax;
    };
    return max_element(trucks.begin(), trucks.end(), func)->volMax;
}

int OptimizeNumberOfDeliveries::getMaxWeightTrucks(const vector<Truck> &trucks) {
    auto func = [](const Truck &left, const Truck &right) {
        return left.pesoMax < right.pesoMax;
    };
    return max_element(trucks.begin(), trucks.end(), func)->pesoMax;
}

int OptimizeNumberOfDeliveries::countTrucksUsedBackTracking(const map<Truck, set<Order *>> &deliveries) {
    auto counter = [](const pair<Truck, set<Order *>> &val) {
        return !val.second.empty();
    };
    return (int) count_if(deliveries.begin(), deliveries.end(), counter);
}

bool
OptimizeNumberOfDeliveries::truckCanStillCarry(const Truck &truck, const set<Order *> &orders, const Order *newOrder) {
    int ordersTotalWeight = 0, ordersTotalVolume = 0;
    for (const Order *order: orders) {
        ordersTotalWeight += order->weight;
        ordersTotalVolume += order->volume;
    }
    bool cond1 = newOrder->weight + ordersTotalWeight > truck.pesoMax;
    bool cond2 = newOrder->volume + ordersTotalVolume > truck.volMax;
    return !(cond1 || cond2);
}

int OptimizeNumberOfDeliveries::getNumberOfDeliveries(const Truck &truck, vector<Order *> &combination) {
    int totalWeightOrders = 0, totalVolumeOrders = 0, count = 0;
    for (const Order *it: combination) {
        totalWeightOrders += it->weight;
        totalVolumeOrders += it->volume;
        count++;
    }
    if (truck.pesoMax >= totalWeightOrders && truck.volMax >= totalVolumeOrders) return count;
    return -1;
}

void OptimizeNumberOfDeliveries::eraseSavedOrders(const vector<Order> &usedItems, vector<Order> &ordersV, bool print) {
    for (const Order order: usedItems) {
        auto it = find(ordersV.begin(), ordersV.end(), order);
        if (it != ordersV.end()) {
            if (print) cout << "\tOrder: " << order.id << "\t\tweight: " << order.weight << "\t\tvolume: " << order.volume << endl;
            ordersV.erase(it);
        }

    }
}

void OptimizeNumberOfDeliveries::printResults(const unsigned &totalDeliveries, const unsigned &numberOfTrucks, const unsigned allOrders) {
    cout << "\nTotal deliveries: " << totalDeliveries << endl;
    cout << "Number of Trucks: " << numberOfTrucks << endl;
    cout << "Time taken: " << Timer::getCurrentTime() << "s\n";
    cout << "Deliveries: "<< totalDeliveries <<" / " << allOrders << " ("<< ((double) totalDeliveries / allOrders) * 100 << "%)" << endl;
}

// NOLINTNEXTLINE
void OptimizeNumberOfDeliveries::getAllDeliveriesCombinations(const unsigned &depth, vector<Order> &orders,
                                                              vector<vector<Order *>> &combinations) {

    if (depth == 0) {
        combinations = {{},
                        {&(orders[0])}};
        getAllDeliveriesCombinations(1, orders, combinations);

    } else if (depth == orders.size())
        return;
    else {
        vector<vector<Order *>> combTemp;
        for (vector<Order *> v: combinations) {
            v.push_back(&(orders[depth]));
            combTemp.push_back(v);
        }
        combinations << combTemp; // append combTemp to combinations
        getAllDeliveriesCombinations(depth + 1, orders, combinations);
    }

}

bool OptimizeNumberOfDeliveries::compareByWeightAndVolume(const Order &o1, const Order &o2) {
    int avg1 = o1.weight * (double) o1.volume;
    int avg2 = o2.weight * (double) o2.volume;
    return avg1 < avg2;
}

unsigned OptimizeNumberOfDeliveries::getGreedyNumberOfOrdersOfTruck(Truck &truck, vector<Order> &orders, vector<Order *>& usedItems) {
    unsigned int numOrders = 0;
    int weightUsed = 0, volumeUsed = 0;
    for (Order &order : orders) {
        if ((weightUsed + order.weight <= truck.pesoMax)   &&   (volumeUsed + order.volume <= truck.volMax)) {
            usedItems.push_back(&order);
            weightUsed += order.weight;
            volumeUsed += order.volume;
            numOrders++;
        }
    }
    return numOrders;
}







// MAIN FUNCTIONS

void OptimizeNumberOfDeliveries::greedyTrucksAndKnapsack(vector<Truck> trucksV, vector<Order> ordersV) {

    Timer::start();

    Memento memento;
    addDayBefore(ordersV, memento);

    vector<Order *> usedItems;
    vector<Order> saveUsedItems;
    unsigned totalDeliveries = 0, numberOfTrucks = 0, allOrders = ordersV.size();

    Knapsack knapsack(ordersV, getMaxWeightTrucks(trucksV), getMaxVolumeTrucks(trucksV));

    do {
        unsigned maxDeliveries = 0;
        int rewardOrders = 0;
        Truck truckChosen{};
        auto itTruckChosen = trucksV.end();
        bool truckFound = false;
        saveUsedItems.clear();
        usedItems.clear();
        knapsack.knapsack_2d_number_deliveries();

        for (auto it = trucksV.begin(); it != trucksV.end(); it++) {
            unsigned numDeliveries = knapsack.get_best_value(it->pesoMax, it->volMax);
            if (numDeliveries > maxDeliveries) {
                maxDeliveries = numDeliveries;
                truckChosen = *it;
                itTruckChosen = it;
                truckFound = true;
                usedItems = knapsack.get_used_items_number_deliveries(it->pesoMax, it->volMax);
            }
        }

        if (truckFound)
            trucksV.erase(itTruckChosen);

        totalDeliveries += maxDeliveries;
        cout << "Truck " << truckChosen.id << ": " << maxDeliveries << " deliveries" << endl;

        for (auto order: usedItems) {
            rewardOrders += order->reward;
            saveUsedItems.push_back(*order);
        }
        memento.save({saveUsedItems, truckChosen.id, rewardOrders - truckChosen.cost});
        eraseSavedOrders(saveUsedItems, ordersV);

        numberOfTrucks++;

    } while (knapsack.getStoreSize() > 0 && !trucksV.empty());
    memento.save({ordersV});

    printResults(totalDeliveries, numberOfTrucks, allOrders);
}

void OptimizeNumberOfDeliveries::greedyTrucksAndGreedyOrders(vector<Truck> trucksV, vector<Order> ordersV) {
    Timer::start();

    Memento memento;
    addDayBefore(ordersV, memento);

    vector<Order *> usedItems, tempUsedItems;
    vector<Order> saveUsedItems;
    unsigned totalDeliveries = 0, numberOfTrucks = 0, allOrders = ordersV.size();

    do {
        Truck truckChosen{};
        auto itTruckChosen = trucksV.end();

        unsigned maxDeliveries = 0;
        int rewardOrders = 0;
        bool truckFound = false;
        saveUsedItems.clear(); tempUsedItems.clear(); usedItems.clear();

        sort(ordersV.begin(), ordersV.end(), compareByWeightAndVolume);
        for (auto it = trucksV.begin(); it != trucksV.end(); it++) {
            unsigned numDeliveries = getGreedyNumberOfOrdersOfTruck(*it, ordersV, tempUsedItems);
            if (numDeliveries > maxDeliveries) {
                maxDeliveries = numDeliveries;
                truckChosen = *it;
                itTruckChosen = it;
                truckFound = true;
                usedItems = tempUsedItems;
                tempUsedItems.clear();
            }
        }

        if (truckFound)
            trucksV.erase(itTruckChosen);

        totalDeliveries += maxDeliveries;
        cout << "Truck " << truckChosen.id << ": " << maxDeliveries << " deliveries" << endl;

        for (auto order: usedItems) {
            rewardOrders += order->reward;
            saveUsedItems.push_back(*order);
        }
        memento.save({saveUsedItems, truckChosen.id, rewardOrders - truckChosen.cost});
        eraseSavedOrders(saveUsedItems, ordersV);

        numberOfTrucks++;

    } while (!ordersV.empty() && !trucksV.empty());

    memento.save({ordersV});
    printResults(totalDeliveries, numberOfTrucks, allOrders);
}

void OptimizeNumberOfDeliveries::greedyTrucksAndBruteForce(vector<Truck> trucksV, vector<Order> ordersV) {

    Timer::start();

    Memento memento;
    addDayBefore(ordersV, memento);
    vector<Order *> usedItems;
    vector<Order> saveUsedItems;
    int totalDeliveries = 0, numberOfTrucks = 0, allOrders = ordersV.size();

    do {
        int maxDeliveries = 0, rewardOrders = 0;
        Truck truckChosen{};
        auto itTruckChosen = trucksV.end();
        bool truckFound = false;
        saveUsedItems.clear();
        usedItems.clear();

        vector<vector<Order *>> combinations;
        getAllDeliveriesCombinations(0, ordersV, combinations);

        for (auto it = trucksV.begin(); it != trucksV.end(); it++)
            for (vector<Order *> &combination: combinations) {
                int numDeliveries = getNumberOfDeliveries(*it, combination);
                if (numDeliveries > maxDeliveries) {
                    maxDeliveries = numDeliveries;
                    truckChosen = *it;
                    itTruckChosen = it;
                    truckFound = true;
                    usedItems = combination;
                }
            }

        if (truckFound)
            trucksV.erase(itTruckChosen);

        totalDeliveries += maxDeliveries;
        cout << "Truck " << truckChosen.id << ": " << maxDeliveries << " deliveries" << endl;

        for (auto order: usedItems) {
            rewardOrders += order->reward;
            saveUsedItems.push_back(*order);
        }
        memento.save({saveUsedItems, truckChosen.id, rewardOrders - truckChosen.cost});
        eraseSavedOrders(saveUsedItems, ordersV);


        numberOfTrucks++;

    } while (!ordersV.empty() && !trucksV.empty());

    memento.saveExpress({ordersV});

    printResults(totalDeliveries, numberOfTrucks, allOrders);
}

void OptimizeNumberOfDeliveries::backtracking(const vector<Truck> &trucksV, vector<Order> ordersV) {

    Timer::start();
    Memento memento;
    addDayBefore(ordersV, memento);

    vector<Order *> orders;
    vector<Order> allUsedOrders;
    int totalDeliveries = 0, numAllOrders , numberOfTrucks;
    map<Truck, set<Order *>> deliveries;

    for (const Truck &truck: trucksV)
        deliveries[truck] = {};

    orders.reserve(ordersV.size());
    for (Order &order: ordersV)
        orders.push_back(&order);

    cout << "\nBacktracking Deliveries...\n";
    numberOfTrucks = backtrackingRec(deliveries, orders, totalDeliveries);

    for (const auto &truckDel: deliveries) {
        int rewardOrders = 0;
        vector<Order> ordersOfThisTruck;
        cout << "Truck " << truckDel.first.id << ": " << truckDel.second.size() << " deliveries" << endl;

        for (const Order *order: truckDel.second) {
            cout << "\tOrder " << order->id << "     weight: " << order->weight << "     volume: " << order->volume
                 << endl;
            rewardOrders += order->reward;
            ordersOfThisTruck.push_back(*order);
            allUsedOrders.push_back(*order);
        }
        memento.save({ordersOfThisTruck, truckDel.first.id, rewardOrders - truckDel.first.cost});
    }
    eraseSavedOrders(allUsedOrders, ordersV, false);
    memento.save({ordersV});
    printResults(totalDeliveries, numberOfTrucks, numAllOrders);
}

// NOLINTNEXTLINE
int OptimizeNumberOfDeliveries::backtrackingRec(map<Truck, set<Order *>> &deliveries, vector<Order *> unselectedOrders,
                                                int &numberOfOrders) {

    if (unselectedOrders.empty()) return countTrucksUsedBackTracking(deliveries);

    Order *order = *unselectedOrders.rbegin();
    unselectedOrders.pop_back();
    map<Truck, set<Order *>> minDeliveries = deliveries, tempDeliveries = deliveries;
    int tempNumberOfOrders = numberOfOrders + 1, minNumberOfOrders = numberOfOrders;

    int tempTrucksUsed, minTrucksUsed = backtrackingRec(minDeliveries, unselectedOrders, minNumberOfOrders);

    for (const auto &truckDeliveries: deliveries)
        if (truckCanStillCarry(truckDeliveries.first, truckDeliveries.second, order)) {

            tempDeliveries[truckDeliveries.first].insert(order);
            tempTrucksUsed = backtrackingRec(tempDeliveries, unselectedOrders, tempNumberOfOrders);

            bool cond1 = tempNumberOfOrders > minNumberOfOrders;
            bool cond2 = (tempNumberOfOrders == minNumberOfOrders) && (tempTrucksUsed < minTrucksUsed);

            if (cond1 || cond2) {
                minNumberOfOrders = tempNumberOfOrders;
                minTrucksUsed = tempTrucksUsed;
                minDeliveries = tempDeliveries;
            }

            tempNumberOfOrders = numberOfOrders;
            tempNumberOfOrders++;
            tempDeliveries[truckDeliveries.first].erase(order);
        }

    unselectedOrders.push_back(order);
    numberOfOrders = minNumberOfOrders;
    deliveries = minDeliveries;
    return minTrucksUsed;
}





