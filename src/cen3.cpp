#include "../include/cen3.h"

int express_scheduling(vector<Order> orders) {

    auto sorter = [](Order a, Order b) {
        return a.duration < b.duration;
    };

    sort(orders.begin(), orders.end(), sorter);

    int total_time = 0, total_profit = 0, i; // 9:00 - 17:00 --> 8h ==> 28800 s

    cout << "\nOrders delivered:\n";
    for (i = 0; i < orders.size(); i++) {
        int dur = orders[i].duration;
        if (total_time + dur > 28800) break;
        total_time += dur;
        total_profit += orders[i].reward;
        cout << orders[i] << endl;
    }

    int success_per = (int) (((float) i / (float) orders.size()) * 100);
    printf("\nTotal time: %ds\nProfit: %d€\nDeliveries: %d / %d (%d%)\n",
           total_time, total_profit, i, (int) orders.size(), success_per);

    if (success_per != 100) {
        cout << "\nOrders not delivered:\n";
        for (; i < orders.size(); i++) {
            cout << orders[i] << endl;
        }
    }

    return total_profit;
}

void cen3() {
    string s2;
    int num_orders, index;

    cout << "num_orders(5,10,45,90,150,225) >> ";
    cin >> num_orders;
    cout << "index >> ";
    cin >> index;
    s2 = "../data/e_" + to_string(num_orders) + "/e_" + to_string(index) + ".txt";


    vector<Order> orders = read_orders(s2);

    if (orders.empty()) {
        cout << "\nInvalid inputs!";
        return;
    }

    /*
        cout << "\nAll orders:\nid volume peso recompensa duração(s)\n";
        for (auto i: orders) cout << i << endl;
    */

    express_scheduling(orders);
}
