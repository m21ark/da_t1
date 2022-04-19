#include "../include/express_deliveries.h"


void express_scheduling(vector<Order> orders) {

    Timer::start();

    Memento memento;
    addDayBefore(orders, memento);

    auto sorter = [](const Order &a, const Order &b) {
        return a.duration < b.duration;
    };

    sort(orders.begin(), orders.end(), sorter); // O(n) = N * log N

    express_scheduling_print(orders, orders.size()); // O(n) = N

    memento.saveExpress(orders);
}


void express_scheduling_bubble(vector<Order> orders) {

    Timer::start();
    Memento memento;
    addDayBefore(orders, memento);

    bubbleSort(orders); // O(n) = N^2

    express_scheduling_print(orders, orders.size()); // O(n) = N^2

    memento.saveExpress(orders);
}

void express_scheduling_brute(vector<Order> orders) {

    Timer::start();
    cout << "\nStarting brute force...\n";

    auto meanTime = [](const vector<Order> &v, const int &maxTime, int &number_of_deliveries) {
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

    vector<Order> best;
    int bestTime = INT32_MAX, number_of_deliveries, best_num_deliveries = 0;

    sort(orders.begin(), orders.end());

    // Test all vector orders permutations to find the best one: O(n)= N!
    do {
        int aux = meanTime(orders, 28800, number_of_deliveries);

        if (number_of_deliveries > best_num_deliveries)
            if (aux <= bestTime) {
                bestTime = aux;
                best = orders;
                best_num_deliveries = number_of_deliveries;
            }

    } while (std::next_permutation(orders.begin(), orders.end()));
    // O(n) = N! --> Test all vector permutations

    express_scheduling_print(best, best_num_deliveries);
}

void express_scheduling_print(vector<Order> &orders, unsigned qnt) {
    cout << "\nOrders delivered:\n";

    int total_time = 0, total_profit = 0, i = 0; // 9:00 - 17:00 --> 8h ==> 28800 s

    auto it = orders.begin();
    for (; it != orders.end(); it++, i++) { // O(n) = n
        if (total_time + it->duration > 28800 || i == qnt) break;

        total_time += it->duration;
        total_profit += it->reward;
        cout << it->id << "\t";
    }
    cout << endl;

    int success_per = (int) (((float) i / (float) orders.size()) * 100);
    printf("\nDelivery time: %ds\nAvg Time: %ds\nProfit: %d€\nDeliveries: %d / %d (%d%%)\n",
           total_time, total_time / i, total_profit, i, (int) orders.size(), success_per);

    orders.erase(orders.begin(), it);
    cout << "Time taken: " << Timer::getCurrentTime() << "s\n";
}


void bubbleSort(vector<Order> &v) {

    auto swap = [](Order *xp, Order *yp) {
        Order temp = *xp;
        *xp = *yp;
        *yp = temp;
        return true;
    };

    int i, j;
    bool swapped;
    for (i = 0; i < v.size() - 1; i++) {
        swapped = false;
        for (j = 0; j < v.size() - i - 1; j++)
            if (v[j + 1].duration < v[j].duration)
                swapped = swap(&v[j], &v[j + 1]);

        if (!swapped)
            break;
    }
}

