#include "../include/cen3.h"

void express_scheduling(vector<Order> orders) {

    auto sorter = [](const Order &a, const Order &b) {
        return a.duration < b.duration;
    };

    sort(orders.begin(), orders.end(), sorter); // O(n) = n log

    int total_time = 0, total_profit = 0, i; // 9:00 - 17:00 --> 8h ==> 28800 s

    cout << "\nOrders delivered:\n";
    for (i = 0; i < orders.size(); i++) { // O(n) = n
        int dur = orders[i].duration;
        if (total_time + dur > 28800) break;
        total_time += dur;
        total_profit += orders[i].reward;
        cout << orders[i] << endl;
    }

    int success_per = (int) (((float) i / (float) orders.size()) * 100);
    printf("\nTotal time: %ds\nAvg Time:%ds\nProfit: %d€\nDeliveries: %d / %d (%d%%)\n",
           total_time, total_time/i ,total_profit, i, (int) orders.size(), success_per);

    if (success_per != 100) {
        cout << "\nOrders not delivered:\n";
        for (; i < orders.size(); i++) {
            cout << orders[i] << endl;
        }
    }
}




void express_scheduling_brute(vector<Order> orders) {

    Timer::start();
    auto meanTime = [](const vector<Order> &v, int maxTime, int &number_of_deliveries) {
        int ret = 0;
        number_of_deliveries = 0;

        for (const Order &i: v) {

            if (ret + i.duration > maxTime)
                break;

            ret += i.duration;

            number_of_deliveries++;
        }

        if (ret * number_of_deliveries == 0) return INT32_MAX;
        return ret / number_of_deliveries;
    };

    vector<Order> best = {};
    int bestTime = INT32_MAX;
    int number_of_deliveries, best_num_deliveries = 0;

    sort(orders.begin(), orders.end());

    do {
        for (auto i: orders) {
            cout << i.id << " ";
        }

        int aux = meanTime(orders, 28800, number_of_deliveries);

        if (aux <= bestTime)
            if (number_of_deliveries > best_num_deliveries) {
                bestTime = aux;
                best = orders;
                best_num_deliveries = number_of_deliveries;
            }
        cout << "\nAvg Time: " << aux << "s\tNum_ords: " << number_of_deliveries << "\n\n";


    } while (std::next_permutation(orders.begin(), orders.end()));

    Timer::stop();
    cout << "\n\nThe best one is:\n";
    for (auto i: best)
        cout << i.id << "(" << i.duration << "s)  ";
    cout << "\nAvg Time: " << bestTime << "s\tNum_ords: " << best_num_deliveries << "\n";

    cout << "The calculation took: " << Timer::getTime() << "s";

}

