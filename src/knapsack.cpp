//
// Created by ricar on 09/04/2022.
//

#include "../include/knapsack.h"

size_t Knapsack::knapsack_2d() {
    const size_t n = store.size();

    // O(n*W*Vo)
    for (size_t i = 0; i <= n; ++i)
    {
        for (size_t j = 0; j <= W; ++j)
        {
            for (size_t k = 0; k <= Vo; ++k) {

                if (i == 0 || j == 0 || k == 0)
                    T[i][j][k] = 0;
                else if (j >= store[i-1].weight && k >= store[i-1].volume)
                {
                    T[i][j][k] = max(T[i -1][j][k],
                                     T[i - 1][j - store[i-1].weight][k - store[i-1].volume] + store[i-1].reward);
                }
                else
                {
                    T[i][j][k] = T[i - 1][j][k];
                }
            }
        }
    }

    size_t value = T[n][W][Vo];

    return value;
}

void Knapsack::knapsack_2d_number_deliveries() {
    for (int i = 0; i <= store.size(); ++i) {
        for (size_t j = 0; j <= W; ++j) {
            for (size_t k = 0; k <= Vo; ++k) {

                if (i == 0 || j == 0 || k == 0) {
                    T[i][j][k] = 0;

                } else if (j >= store[i-1].weight && k >= store[i-1].volume) {
                    T[i][j][k] = max(T[i -1][j][k],
                                     T[i - 1][j - store[i-1].weight][k - store[i-1].volume] + 1);

                } else {
                    T[i][j][k] = T[i - 1][j][k];
                }
            }
        }
    }

}

void Knapsack::print_knapsack() {

    size_t w = W;
    size_t v = Vo;
    size_t n = store.size();

    int res= T[n][W][Vo];

    for (size_t i = n; i > 0 && res > 0; i--) {

        if (res == T[i - 1][w][v])
            continue;
        else {
            //cout <<store[i - 1].volume   << " " <<store[i - 1].weight << " " << store[i - 1].reward << endl;
            cout << store[i-1].id << endl;
            res = res - store[i - 1].reward;
            w = w - store[i - 1].weight;
            v = v - store[i - 1].volume;
        }
    }

    /*cout    << "......................." << endl;
    for (size_t i = 0; i <= n; ++i)
    {
        for (size_t j = 0; j <= W; ++j)
        {
            for (size_t k = 0; k <= Vo; ++k) {

                cout << T[i][j][k] << " ";
            }
            cout   << endl;
        }
        cout << endl;
    }
    cout    << "......................." << endl;*/

}

size_t Knapsack::get_best_value(size_t WeightCapacity, size_t VolumeCapacity) {
    return T[store.size()][WeightCapacity][VolumeCapacity];
}

vector<Order *> Knapsack::get_used_items(size_t W, size_t Vo) {
    vector<Order *> used_item;
    size_t w = W;
    size_t v = Vo;
    size_t n = store.size();

    size_t res= T[n][W][Vo];

    for (size_t i = n; i > 0 && res > 0; i--) {

        if (res == T[i - 1][w][v])
            continue;
        else {
            used_item.push_back(&store[i-1]);

            res = res - store[i - 1].reward;
            w = w - store[i - 1].weight;
            v = v - store[i - 1].volume;
        }
    }

    return used_item;
}

double Knapsack::fractionalKnapsack(vector<Order *>& usedItems, size_t W, size_t Vo) {

    sort(store.begin(), store.end(), [](const Order& l, const Order& r)
    {return (double)l.reward/ (double)(l.weight+l.volume) > (double)r.reward/(double)(r.weight+r.volume);});

    int cur_weight = 0;
    int cur_volume = 0;

    double final_val = 0.0;
    n = store.size();
    for(int i=0;i<n;i++)
    {
        if(cur_weight + store[i].weight <= W && cur_volume + store[i].volume <= Vo)
        {
            cur_weight += store[i].weight;
            cur_volume += store[i].volume;
            final_val += store[i].reward;
            usedItems.push_back(&store[i]);
        }
        else
        {
            //int remainW = W - cur_weight;
            //int remainV = Vo - cur_volume;

            //final_val += store[i].reward * ((double)(remainV * remainW) / (store[i].weight + store[i].volume));
            break;
        }
    }
    return final_val;
}
























