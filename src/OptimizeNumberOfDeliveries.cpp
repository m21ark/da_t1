#include "../include/OptimizeNumberOfDeliveries.h"


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

int OptimizeNumberOfDeliveries::greedyTrucksAndKnapsack(const std::string & del, const std::string& trucks) {
    vector<Order> ordersV = read_orders(del);
    vector<Truck> trucksV = read_trucks(trucks);
    vector<Order*> usedItems;
    int totalDeliveries = 0, numberOfTrucks = 0;

    cout << "Trucks" << endl;
    for (Truck &t : trucksV) cout << "truck " << t.id << "    weight capacity: " << t.pesoMax << "    volume capacity: " << t.volMax << endl;
    cout << "\nOrders" << endl;
    for (Order &o : ordersV) cout << "order " << o.id << "    weight: " << o.weight << "    volume: " << o.volume << endl;

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
        for (auto order : usedItems) cout << "\tOrder " << order->id << "     weight: " << order->weight << "     volume: " << order->volume << endl;

        for (auto order : usedItems) {
            auto it = std::find(ordersV.begin(), ordersV.end(), *order);
            if ( it != ordersV.end())
                ordersV.erase(it);
        }

        numberOfTrucks++;


    } while (knapsack.getStoreSize() > 0 && numberOfTrucks < trucksV.size());

    cout << "Total deliveries: " << totalDeliveries << endl;
    return totalDeliveries;
}

int OptimizeNumberOfDeliveries::bruteForce(const string &del, const string &trucks) {
    vector<Order> ordersV = read_orders(del);
    vector<Truck> trucksV = read_trucks(trucks);

    //passar uma lista em vez de vectors visto fazer muitos inserts e erases
    return recursiveBruteForce(trucksV, ordersV);
}

int OptimizeNumberOfDeliveries::recursiveBruteForce(vector<Truck> trucks, vector<Order> orders) {
    /*
    if (orders.empty() || trucks.empty()) return 0;

    for (int i = 0; i < trucks.size(); ) {



    }
    */
    return 0;
}


