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
    printf("\nTotal time: %ds\nProfit: %d€\nDeliveries: %d / %d (%d%%)\n",
           total_time, total_profit, i, (int) orders.size(), success_per);

    if (success_per != 100) {
        cout << "\nOrders not delivered:\n";
        for (; i < orders.size(); i++) {
            cout << orders[i] << endl;
        }
    }
}


void express_scheduling_brute(vector<Order> orders) {

}

