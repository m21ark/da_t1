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


int main() {
    // maybe it's missing the duration variable --8 is best sol.
    vector<Order> v = read_orders("../data/e_10/e2.txt");

    Knapsack knapsack(v);

    knapsack.knapsack_2d(395,391); //c1/ c_1 391 395 13796

    knapsack.print_knapsack(395,391);

    return 0;
}
