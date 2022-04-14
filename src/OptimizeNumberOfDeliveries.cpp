#include "../include/OptimizeNumberOfDeliveries.h"

// Auxiliary Functions
int OptimizeNumberOfDeliveries::getMaxVolumeTrucks(vector<Truck> &trucks) {
    int maxVol = INT32_MIN;
    for (Truck &t: trucks)
        if (t.volMax > maxVol) maxVol = t.volMax; //TODO More efficient func?
    return maxVol;
}

int OptimizeNumberOfDeliveries::getMaxWeightTrucks(vector<Truck> &trucks) {
    int maxWeight = INT32_MIN;
    for (Truck &t: trucks) {
        if (t.pesoMax > maxWeight) maxWeight = t.pesoMax; //TODO More efficient func?
    }
    return maxWeight;
}

// NOLINTNEXTLINE
void OptimizeNumberOfDeliveries::getAllDeliveriesCombinations(unsigned int depth, vector<Order> &orders,
                                                              vector<vector<Order *>> &combinations) {
    if (depth == 0) {
        combinations = {{},
                        {&(orders[0])}};
        getAllDeliveriesCombinations(1, orders, combinations);

    } else if (depth == orders.size()) {
        return;

    } else {
        vector<vector<Order *>> combTemp;
        for (vector<Order *> v: combinations) {
            v.push_back(&(orders[depth]));
            combTemp.push_back(v);
        }
        for (const vector<Order *> &v: combTemp)
            combinations.push_back(v);

        getAllDeliveriesCombinations(depth + 1, orders, combinations);
    }

}

int OptimizeNumberOfDeliveries::getNumberOfDeliveries(Truck truck, vector<Order *> &combination) {
    int totalWeightOrders = 0, totalVolumeOrders = 0, count = 0;
    for (Order *it: combination) {
        totalWeightOrders += it->weight;
        totalVolumeOrders += it->volume;
        count++;
    }

    if (truck.pesoMax >= totalWeightOrders && truck.volMax >= totalVolumeOrders) return count;
    return -1;
}

int OptimizeNumberOfDeliveries::countTrucksUsedBackTracking(map<Truck, set<Order *>> &deliveries) {
    int counter = 0;
    for (auto &delivery: deliveries) //TODO More efficient func?
        if (!delivery.second.empty()) counter++;
    return counter;
}

bool OptimizeNumberOfDeliveries::truckCanStillCarry(Truck truck, set<Order *> &orders, Order *newOrder) {
    int ordersTotalWeight = 0, ordersTotalVolume = 0;
    for (Order *order: orders) {
        ordersTotalWeight += order->weight;
        ordersTotalVolume += order->volume;
    }

    bool cond1 = newOrder->weight + ordersTotalWeight > truck.pesoMax;
    bool cond2 = newOrder->volume + ordersTotalVolume > truck.volMax;

    return !(cond1 || cond2);
}


// MAIN FUNCTIONS

void OptimizeNumberOfDeliveries::greedyTrucksAndKnapsack(vector<Truck> trucksV, vector<Order> ordersV) {

    Timer::start();

    Knapsack knapsack(ordersV, getMaxWeightTrucks(trucksV), getMaxVolumeTrucks(trucksV));
    unsigned totalDeliveries = 0, numberOfTrucks = 0;
    vector<Order *> usedItems;

    do {
        unsigned maxDeliveries = 0;
        Truck truckChosen{};
        auto itTruckChosen = trucksV.end();
        bool truckFound = false;
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
        vector<Order> saveUsedItems;
        for (auto order: usedItems) {
            cout << "\tOrder " << order->id << "     weight: " << order->weight << "     volume: " << order->volume
                 << endl;
            saveUsedItems.push_back(*order);
        }

        for (auto order: saveUsedItems) {
            auto it = std::find(ordersV.begin(), ordersV.end(), order);
            if (it != ordersV.end())
                ordersV.erase(it);
        }

        numberOfTrucks++;

    } while (knapsack.getStoreSize() > 0 && !trucksV.empty());

    Timer::stop();

    cout << "\nTotal deliveries: " << totalDeliveries << endl;
    cout << "Number of Trucks: " << numberOfTrucks << endl;
    cout << "Time taken: " << Timer::getTime() << "s\n";
}


void OptimizeNumberOfDeliveries::greedyTrucksAndBruteForce(vector<Truck> trucksV, vector<Order> ordersV) {

    Timer::start();

    vector<Order *> usedItems;
    int totalDeliveries = 0, numberOfTrucks = 0;

    do {
        int maxDeliveries = 0;
        Truck truckChosen{};
        auto itTruckChosen = trucksV.end();
        bool truckFound = false;

        vector<vector<Order *>> combinations;
        getAllDeliveriesCombinations(0, ordersV, combinations);

        for (auto it = trucksV.begin(); it != trucksV.end(); it++) {
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
        }

        if (truckFound) {
            trucksV.erase(itTruckChosen);
        }

        totalDeliveries += maxDeliveries;
        cout << "Truck " << truckChosen.id << ": " << maxDeliveries << " deliveries" << endl;
        vector<Order> saveUsedItems;
        for (auto order: usedItems) {
            cout << "\tOrder " << order->id << "     weight: " << order->weight << "     volume: " << order->volume
                 << endl;
            saveUsedItems.push_back(*order);
        }

        for (auto order: saveUsedItems) {
            auto it = std::find(ordersV.begin(), ordersV.end(), order);
            if (it != ordersV.end())
                ordersV.erase(it);
        }

        numberOfTrucks++;

    } while (!ordersV.empty() && !trucksV.empty());

    Timer::stop();

    cout << "\nTotal deliveries: " << totalDeliveries << endl;
    cout << "Number of Trucks: " << numberOfTrucks << endl;
    cout << "Time taken: " << Timer::getTime() << "s\n";

}

void OptimizeNumberOfDeliveries::backtracking(const vector<Truck> &trucksV, vector<Order> ordersV) {

    Timer::start();

    map<Truck, set<Order *>> deliveries;
    vector<Order *> orders;
    int totalDeliveries = 0, numberOfTrucks;

    for (Truck truck: trucksV) deliveries[truck] = {};
    orders.reserve(ordersV.size());
    for (Order &order: ordersV) orders.push_back(&order);

    cout << "\nBacktracking Deliveries..." << endl;
    numberOfTrucks = backtrackingRec(deliveries, orders, totalDeliveries);

    for (const auto &truckDel: deliveries) {
        cout << "Truck " << truckDel.first.id << ": " << truckDel.second.size() << " deliveries" << endl;
        for (Order *order: truckDel.second) {
            cout << "\tOrder " << order->id << "     weight: " << order->weight << "     volume: " << order->volume
                 << endl;
        }
    }

    Timer::stop();

    cout << "\nTotal deliveries: " << totalDeliveries << endl;
    cout << "Number of Trucks: " << numberOfTrucks << endl;
    cout << "Time taken: " << Timer::getTime() << "s\n";
}

// NOLINTNEXTLINE
int OptimizeNumberOfDeliveries::backtrackingRec(map<Truck, set<Order *>> &deliveries, vector<Order *> unselectedOrders,
                                                int &numberOfOrders) {

    if (unselectedOrders.empty()) return countTrucksUsedBackTracking(deliveries);
    Order *order = *unselectedOrders.rbegin();
    unselectedOrders.pop_back();

    map<Truck, set<Order *>> minDeliveries = deliveries, tempDeliveries = deliveries;
    int tempNumberOfOrders = numberOfOrders, minNumberOfOrders = numberOfOrders;

    int tempTrucksUsed, minTrucksUsed = backtrackingRec(minDeliveries, unselectedOrders, minNumberOfOrders);
    tempNumberOfOrders++;

    for (auto &truckDeliveries: deliveries) {

        if (truckCanStillCarry(truckDeliveries.first, truckDeliveries.second, order)) {
            tempDeliveries[truckDeliveries.first].insert(order);
            tempTrucksUsed = backtrackingRec(tempDeliveries, unselectedOrders, tempNumberOfOrders);

            bool cond1 = tempNumberOfOrders > minNumberOfOrders;
            bool cond2 = tempNumberOfOrders == minNumberOfOrders && tempTrucksUsed < minTrucksUsed;

            if (cond1 || cond2) {
                minNumberOfOrders = tempNumberOfOrders;
                minTrucksUsed = tempTrucksUsed;
                minDeliveries = tempDeliveries;
            }

            tempNumberOfOrders = numberOfOrders;
            tempNumberOfOrders++;
            tempDeliveries[truckDeliveries.first].erase(order);
        }
    }

    unselectedOrders.push_back(order);
    numberOfOrders = minNumberOfOrders;
    deliveries = minDeliveries;
    return minTrucksUsed;
}





