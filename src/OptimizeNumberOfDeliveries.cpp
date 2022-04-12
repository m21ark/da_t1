#include "../include/OptimizeNumberOfDeliveries.h"


// Auxiliary Functions
int OptimizeNumberOfDeliveries::getMaxVolumeTrucks(vector<Truck>& trucks) {
    int maxVol = INT32_MIN;
    for (Truck &t : trucks) {
        if (t.volMax > maxVol) maxVol = t.volMax;
    }
    return maxVol;
}

int OptimizeNumberOfDeliveries::getMaxWeightTrucks(vector<Truck> &trucks) {
    int maxWeight = INT32_MIN;
    for (Truck &t : trucks) {
        if (t.pesoMax > maxWeight) maxWeight = t.pesoMax;
    }
    return maxWeight;
}

void OptimizeNumberOfDeliveries::getAllDeliveriesCombinations(unsigned int depth, vector<Order> &orders, vector<vector<Order*>>& combinations) {
    if (depth == 0) {
        combinations = {{}, {&(orders[0])}};
        getAllDeliveriesCombinations(1, orders, combinations);

    } else if (depth == orders.size()) {
        return;

    } else {
        vector<vector<Order*>> combTemp;
        for (vector<Order*> v : combinations) {
            v.push_back(&(orders[depth]));
            combTemp.push_back(v);
        }
        for (vector<Order*> v : combTemp) {
            combinations.push_back(v);
        }
        getAllDeliveriesCombinations(depth + 1, orders, combinations);
    }

}

int OptimizeNumberOfDeliveries::getNumberOfDeliveries(Truck truck, vector<Order *>& combination) {
    int totalWeightOrders = 0, totalVolumeOrders = 0, count = 0;
    for (Order* it : combination) {
        totalWeightOrders += it->weight;
        totalVolumeOrders += it->volume;
        count++;
    }

    if (truck.pesoMax >= totalWeightOrders && truck.volMax >= totalVolumeOrders) return count;
    return -1;
}









// MAIN FUNCTIONS

void OptimizeNumberOfDeliveries::greedyTrucksAndKnapsack(const std::string & del, const std::string& trucks) {
    vector<Order> ordersV = read_orders(del);
    vector<Truck> trucksV = read_trucks(trucks);
    vector<Order*> usedItems;
    int totalDeliveries = 0, numberOfTrucks = 0;

    cout << "\nGreedy Trucks and Knapsack Orders" << endl;
    /*
    cout << "Trucks" << endl;
    for (Truck &t : trucksV) cout << "truck " << t.id << "    weight capacity: " << t.pesoMax << "    volume capacity: " << t.volMax << endl;
    cout << "\nOrders" << endl;
    for (Order &o : ordersV) cout << "order " << o.id << "    weight: " << o.weight << "    volume: " << o.volume << endl;
    */
    Knapsack knapsack(ordersV, getMaxWeightTrucks(trucksV), getMaxVolumeTrucks(trucksV));

    do {
        int maxDeliveries = 0;
        Truck truckChosen;
        auto itTruckChosen = trucksV.end();
        bool truckFound = false;
        knapsack.knapsack_2d_number_deliveries();

        for (auto it = trucksV.begin(); it != trucksV.end(); it++) {
            int numDeliveries = knapsack.get_best_value(it->pesoMax, it->volMax);
            if (numDeliveries > maxDeliveries) {
                maxDeliveries = numDeliveries;
                truckChosen = *it;
                itTruckChosen = it;
                truckFound = true;
                usedItems = knapsack.get_used_items_number_deliveries(it->pesoMax, it->volMax);
            }
        }

        if (truckFound) {
            trucksV.erase(itTruckChosen);
        }

        totalDeliveries += maxDeliveries;
        cout << "Truck " << truckChosen.id << ": " << maxDeliveries << " deliveries" << endl;
        vector<Order> saveUsedItems;
        for (auto order : usedItems) {
            cout << "\tOrder " << order->id << "     weight: " << order->weight << "     volume: " << order->volume << endl;
            saveUsedItems.push_back(*order);
        }

        for (auto order : saveUsedItems) {
            auto it = std::find(ordersV.begin(), ordersV.end(), order);
            if ( it != ordersV.end())
                ordersV.erase(it);
        }

        numberOfTrucks++;
        /*
        cout << "Orders left: " << knapsack.getStoreSize() << endl;
        cout << "trucksV size: " << trucksV.size() << endl;
         */
    } while (knapsack.getStoreSize() > 0 && !trucksV.empty());

    cout << "Total deliveries: " << totalDeliveries << endl;
    cout << "Number of Trucks: " << numberOfTrucks << endl;
}


void OptimizeNumberOfDeliveries::greedyTrucksAndBruteForce(const std::string &del, const std::string &trucks) {
    vector<Order> ordersV = read_orders(del);
    vector<Truck> trucksV = read_trucks(trucks);
    vector<Order*> usedItems;
    int totalDeliveries = 0, numberOfTrucks = 0;


    cout << "\nGreedy Trucks and Brute Force Orders" << endl;
    /*
    cout << "Trucks" << endl;
    for (Truck &t : trucksV) cout << "truck " << t.id << "    weight capacity: " << t.pesoMax << "    volume capacity: " << t.volMax << endl;
    cout << "\nOrders" << endl;
    for (Order &o : ordersV) cout << "order " << o.id << "    weight: " << o.weight << "    volume: " << o.volume << endl;
    */

    do {
        int maxDeliveries = 0;
        Truck truckChosen;
        auto itTruckChosen = trucksV.end();
        bool truckFound = false;

        vector<vector<Order*>> combinations;
        getAllDeliveriesCombinations(0, ordersV, combinations);

        for (auto it = trucksV.begin(); it != trucksV.end(); it++) {
            for (vector<Order*> &combination : combinations) {
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
        for (auto order : usedItems) {
            cout << "\tOrder " << order->id << "     weight: " << order->weight << "     volume: " << order->volume << endl;
            saveUsedItems.push_back(*order);
        }

        for (auto order : saveUsedItems) {
            auto it = std::find(ordersV.begin(), ordersV.end(), order);
            if ( it != ordersV.end())
                ordersV.erase(it);
        }

        numberOfTrucks++;
        /*
        cout << "Orders left: " << knapsack.getStoreSize() << endl;
        cout << "trucksV size: " << trucksV.size() << endl;
         */
    } while (!ordersV.empty() && !trucksV.empty());

    cout << "Total deliveries: " << totalDeliveries << endl;
    cout << "Number of Trucks: " << numberOfTrucks << endl;
}

void OptimizeNumberOfDeliveries::backtracking(const string &del, const string &trucks) {
    vector<Order> ordersV = read_orders(del);
    vector<Truck> trucksV = read_trucks(trucks);
    map<Truck, set<Order*>> deliveries;
    set<Order*> orders;
    int totalDeliveries = 0, numberOfTrucks = 0;

    for (Truck truck : trucksV) deliveries[truck] = {};
    for (Order &order : ordersV) orders.insert(&order);

    cout << "\nBacktracking Deliveries" << endl;
    numberOfTrucks = backtrackingRec(deliveries, orders, totalDeliveries);

    for (auto truckDel : deliveries) {
        cout << "Truck " << truckDel.first.id << ": " << truckDel.second.size() << " deliveries" << endl;
        for (Order* order : truckDel.second) {
            cout << "\tOrder " << order->id << "     weight: " << order->weight << "     volume: " << order->volume << endl;
        }
    }

    cout << "Total deliveries: " << totalDeliveries << endl;
    cout << "Number of Trucks: " << numberOfTrucks << endl;
}

int OptimizeNumberOfDeliveries::countTrucksUsedBackTracking(map<Truck, set<Order *>> &deliveries) {
    int counter = 0;
    for (auto it = deliveries.begin(); it != deliveries.end(); it++) {
        if (!it->second.empty()) counter++;
    }
    return counter;
}

int OptimizeNumberOfDeliveries::backtrackingRec(map<Truck, set<Order*>>& deliveries, set<Order*>& unselectedOrders, int& numberOfOrders) {
    if (unselectedOrders.empty()) return countTrucksUsedBackTracking(deliveries);

    Order* order = *unselectedOrders.begin(); unselectedOrders.erase(order);
    map<Truck, set<Order*>> minDeliveries = deliveries;
    int tempTrucksUsed, tempNumberOfOrders = numberOfOrders;
    int minTrucksUsed = backtrackingRec(minDeliveries, unselectedOrders, tempNumberOfOrders);
    numberOfOrders++;

    for (auto &truckDeliveries : deliveries) {
        // still need to check if I can insert order Vol and weight use an if
        truckDeliveries.second.insert(order);

        tempTrucksUsed = backtrackingRec(deliveries, unselectedOrders, tempNumberOfOrders);
        if (tempNumberOfOrders > numberOfOrders) {
            numberOfOrders = tempNumberOfOrders;
            minTrucksUsed = tempTrucksUsed;
            minDeliveries = deliveries;
        }

        truckDeliveries.second.erase(order);

    }

    //insert order again
    return 0;
}





