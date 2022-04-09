//
// Created by ricar on 09/04/2022.
//

#include "../include/knapsack.h"

size_t Knapsack::knapsack_2d(const size_t WeightCapacity, const size_t VolumeCapacity) {
    const size_t n = store.size();
    const size_t W = WeightCapacity ;
    const size_t Vo = VolumeCapacity;

    T = vector<vector<vector<size_t>>>(n + 1, vector<vector<size_t>>(W +1, vector<size_t>(Vo +1)));

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

void Knapsack::print_knapsack(const size_t W, const size_t Vo) {
    size_t w = W;
    size_t v = Vo;
    size_t n = store.size();

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
