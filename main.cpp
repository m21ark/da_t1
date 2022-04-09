#include <iostream>
#include "include/read_files.h"

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
    vector<Order> v;

    v.push_back({2,1,2,5});
    v.push_back({1,2,3,4});
    v.push_back({3,1,3,5});
    v.push_back({2,3,4,4});
    v.push_back({2,2,4,5});
    v.push_back({3,3,5,4});

    cout << knapsack_2d(v,6,4) << endl; // see http://user.engineering.uiowa.edu/~dbricker/Stacks_pdf1/MultiDim_Knapsack.pdf
    // slide 5
    v.clear();
    v.push_back({2,1,2,5});
    v.push_back({1,2,3,4});
    v.push_back({3,1,3,5});
    v.push_back({2,3,4,4});
    v.push_back({2,2,4,5});
    v.push_back({3,3,5,4});
    v.push_back({4,6,900,4});

    cout << knapsack_2d(v,700,600); // see http://user.engineering.uiowa.edu/~dbricker/Stacks_pdf1/MultiDim_Knapsack.pdf


    return 0;
}
