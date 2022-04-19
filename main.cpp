#include "include/menu.h"

using namespace std;

void testing() {

    vector<float> times;

    int num_trucks = 5;
    int num_orders = 5;

    int truck_ids = 10;
    int orders_ids = 10;

    for (int i = 1; i <= orders_ids; i++) {

        string trucks_f = "../data/c_" + to_string(num_trucks) + "/c_" + to_string(i % truck_ids + 1) + ".txt";
        string orders_f = "../data/e_" + to_string(num_orders) + "/e_" + to_string(i) + ".txt";

        vector<Truck> trucks = read_trucks(trucks_f);
        vector<Order> orders = read_orders(orders_f);

        Timer::start();

        OptimizeNumberOfDeliveries::greedyTrucksAndKnapsack(trucks, orders);

        times.push_back(Timer::getCurrentTime());

        if (i == 1) getchar();
        system(CLEAR);
    }


    /*  PRINTING RESULTS  */

    int count = 0;
    float sum = 0;

    for (auto i: times) {
        count++;
        sum += i;
    }

    printf("\nCount: %d\nSum: %f", count, sum);
    cout << "\n\nMean: " << sum / (float) count;

    getchar();
}


int main() {
    //testing();
    Menu::start();
    return 0;
}
