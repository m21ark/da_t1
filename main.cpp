#include <iostream>
#include "include/read_files.h"
#include "include/knapsack.h"

void print_knapsack(const vector<vector<vector<size_t>> >& T,const size_t n,const size_t W, const size_t Vo, const vector<Order>& store) {
    size_t w = W;
    size_t v = Vo;

    size_t res= T[n][W][Vo];

    for (size_t i = n; i > 0 && res > 0; i--) {

        if (res == T[i - 1][w][v])
            continue;
        else {
            cout <<store[i - 1].volume   << " " <<store[i - 1].weight << " " << store[i - 1].reward << endl;

            res = res - store[i - 1].reward;
            w = w - store[i - 1].weight;
            v = v - store[i - 1].volume;
        }
    }
}

size_t knapsack_2d(vector<Order>& store, const size_t WeightCapacity, const size_t VolumeCapacity)
{
    const size_t n = store.size();
    const size_t W = WeightCapacity ;
    const size_t Vo = VolumeCapacity;

    vector<vector<vector<size_t>> > T(n + 1, vector<vector<size_t>>(W +1, vector<size_t>(Vo +1)));

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

    print_knapsack(T,n, W, Vo,store);

    return value;
}

#include "include/cen3.h"

#include <chrono>
using namespace std::chrono;

using namespace std;

int main() {
    // cen3();

    vector<Order> v = read_orders("../data/encomendas.txt");

    Knapsack knapsack(v);

    vector<Truck> t = read_trucks("../data/carrinhas.txt");
    auto start = high_resolution_clock::now();
    vector<int> profit;
    vector<Order *> used_items;
    int i = v.size();
    size_t p = 0;
    do {
        knapsack.knapsack_2d(400,400); // TODO:CHANGE

        int max_prof = INT_MIN;

        for (auto &truck: t) {
            int prof = ((int)knapsack.get_best_value(truck.pesoMax, truck.volMax) - truck.cost);
            if (prof > max_prof) {
                max_prof = prof;
                used_items = knapsack.get_used_items(truck.pesoMax, truck.volMax);
            }
        }
        p++;
        profit.push_back(max_prof);


        for (auto e : used_items) {
            auto it = std::find(v.begin(), v.end(), *e);
            if ( it != v.end())
                v.erase(it);
        }

        i-=used_items.size();
        cout << i << " " << p << " " <<  used_items.size() << " " << v.size() << " " << max_prof << endl;
    } while (i > 0 && p != t.size());

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);
    cout << duration.count() << endl;
    int comul_prof = 0;
    for (auto & pr: profit) {
        comul_prof += pr;
    }
    cout << "PROF = " << comul_prof <<endl;
    return 0;
}
