#include "../include/knapsack.h"

size_t Knapsack::knapsack_2d() {
    const size_t size = store.size();

    // O(size*W*Vo)
    for (size_t i = 0; i <= size; ++i)
        for (size_t j = 0; j <= W; ++j)
            for (size_t k = 0; k <= Vo; ++k) {

                if (i == 0 || j == 0 || k == 0)
                    T[i][j][k] = 0;
                else if (j >= store[i - 1].weight && k >= store[i - 1].volume)
                    T[i][j][k] = max(T[i - 1][j][k],
                                     T[i - 1][j - store[i - 1].weight][k - store[i - 1].volume] + store[i - 1].reward);
                else
                    T[i][j][k] = T[i - 1][j][k];
            }

    return T[size][W][Vo];
}

void Knapsack::knapsack_2d_number_deliveries() {

    for (size_t i = 0; i <= store.size(); i++)
        for (size_t j = 0; j <= W; j++)
            for (size_t k = 0; k <= Vo; k++) {

                if (i == 0 || j == 0 || k == 0)
                    T[i][j][k] = 0;
                else if (j >= store[i - 1].weight && k >= store[i - 1].volume)
                    T[i][j][k] = max(T[i - 1][j][k], T[i - 1][j - store[i - 1].weight][k - store[i - 1].volume] + 1);
                else
                    T[i][j][k] = T[i - 1][j][k];
            }
}

void Knapsack::print_knapsack() {

    size_t w = W, v = Vo, size = store.size();
    size_t res = T[size][W][Vo];

    for (size_t i = size; i > 0 && res > 0; i--) {

        if (res == T[i - 1][w][v])
            continue;
        else {
            cout << store[i - 1].id << endl;
            res = res - store[i - 1].reward;
            w = w - store[i - 1].weight;
            v = v - store[i - 1].volume;
        }
    }

}

size_t Knapsack::get_best_value(size_t WeightCapacity, size_t VolumeCapacity) {
    return T[store.size()][WeightCapacity][VolumeCapacity];
}

vector<Order> Knapsack::get_used_items(size_t weight, size_t volume) {

    size_t w = weight, v = volume, size = store.size();
    size_t res = T[size][weight][volume];
    vector<Order> used_item;

    for (size_t i = size; i > 0 && res > 0; i--) {

        if (res == T[i - 1][w][v])
            continue;
        else {
            used_item.push_back(store[i - 1]);
            res = res - store[i - 1].reward;
            w = w - store[i - 1].weight;
            v = v - store[i - 1].volume;
        }
    }

    return used_item;
}

double Knapsack::fractionalKnapsack(vector<Order> &usedItems, size_t wight, size_t weight) {

    auto sorter = [](const Order &l, const Order &r) {
        return (double) l.reward / (double) (l.weight + l.volume) > (double) r.reward / (double) (r.weight + r.volume);
    };

    sort(store.begin(), store.end(), sorter);

    int cur_weight = 0, cur_volume = 0;
    double final_val = 0.0;
    n = store.size();

    for (int i = 0; i < n; i++) {
        if (cur_weight + store[i].weight <= wight && cur_volume + store[i].volume <= weight) {
            cur_weight += store[i].weight;
            cur_volume += store[i].volume;
            final_val += store[i].reward;
            usedItems.push_back(store[i]);
        } else
            break;
    }
    return final_val;
}


vector<Order *> Knapsack::get_used_items_number_deliveries(size_t weight, size_t volume) {
    vector<Order *> used_item;
    size_t w = weight;
    size_t v = volume;
    size_t size = store.size();

    size_t numDel = T[size][weight][volume];

    for (size_t i = size; i > 0 && numDel > 0; i--) {

        if (numDel == T[i - 1][w][v])
            continue;
        else {
            used_item.push_back(&store[i - 1]);

            numDel--;
            w = w - store[i - 1].weight;
            v = v - store[i - 1].volume;
        }
    }

    return used_item;
}
