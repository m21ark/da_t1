#include "../include/knapsack.h"

void Knapsack::knapsack_calc(size_t i, size_t j, size_t k, int increment) {
    if (i == 0 || j == 0 || k == 0)
        T[i][j][k] = 0;
    else if (j >= store[i - 1].weight && k >= store[i - 1].volume)
        T[i][j][k] = max(T[i - 1][j][k], T[i - 1][j - store[i - 1].weight][k - store[i - 1].volume] + increment);
    else
        T[i][j][k] = T[i - 1][j][k];
}

size_t Knapsack::knapsack_2d() {
    const size_t size = store.size();

    for (size_t i = 0; i <= size; ++i)  // O(size*W*Vo)
        for (size_t j = 0; j <= W; ++j)
            for (size_t k = 0; k <= Vo; ++k)
                knapsack_calc(i, j, k, i == 0 ? 0 : store[i - 1].reward);

    return T[size][W][Vo];
}

void Knapsack::knapsack_2d_number_deliveries() {
    for (size_t i = 0; i <= store.size(); i++)
        for (size_t j = 0; j <= W; j++)
            for (size_t k = 0; k <= Vo; k++)
                knapsack_calc(i, j, k, 1);
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

size_t Knapsack::get_best_value(const size_t &WeightCapacity, const size_t &VolumeCapacity) {
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
    size_t w = weight, v = volume;
    size_t size = store.size();
    size_t numDel = T[size][weight][volume];

    for (size_t i = size; i > 0 && numDel > 0; i--) {
        if (numDel == T[i - 1][w][v])
            continue;
        else {
            used_item.push_back(&store[i - 1]);
            numDel--;
            w -= store[i - 1].weight;
            v -= store[i - 1].volume;
        }
    }
    return used_item;
}

vector<vector<pair<int, int>>> Knapsack::optimal_cost(const vector<Order> &v, int wCap, int vCap) {
    vector<vector<pair<int, int>>> dp(wCap + 1, vector<pair<int, int>>(vCap + 1, {0, -1}));

    for (int i = 0; i < size(v); ++i) {
        for (int j = wCap; j >= 0; --j) {
            for (int k = vCap; k >= 0; --k) {
                if (v[i].weight <= j && v[i].volume <= k
                    && dp[j][k].first < dp[j - v[i].weight][k - v[i].volume].first + v[i].reward
                        ) {
                    dp[j][k] = {dp[j - v[i].weight][k - v[i].volume].first + v[i].reward, i};
                }
            }
        }
    }

    return dp;
}

int closest(std::vector<int> const &vec, int value) {
    auto const it = std::lower_bound(vec.begin(), vec.end(), value);
    if (it == vec.end()) { return -1; }

    return *it;
}


//adaptado de https://stackoverflow.com/questions/36834028/reconstructing-the-list-of-items-from-a-space-optimized-0-1-knapsack-implementat
vector<int>
Knapsack::knapsack_hirschberg(const vector<Order> &v, int wCap, int vCap, int &mProf, vector<Truck> &trucks, int offset,
                              bool firs) {
    if (empty(v))
        return {};

    pair<int, pair<int, int>> best = {-1, {-1, -1}};
    if (firs) {
        auto sol = optimal_cost(v, wCap, vCap);
        pair<int, pair<int, int>> max = {-1, {-1, -1}};
        int a = 0, b = 0;
        for (auto truck = trucks.begin(); truck != trucks.end(); truck++) {
            int prof = sol[truck->pesoMax][truck->volMax].first - truck->cost;
            if (prof > max.first) {
                max = {prof, {truck->pesoMax, truck->volMax}};
                mProf = prof;
                a = truck->pesoMax;
                b = truck->volMax;
                itTruck = truck;
            }
        }
        if (a != 0) {
            wCap = a;
            vCap = b;
        }

        return knapsack_hirschberg(v, wCap, vCap, mProf, trucks, 0, false);
    }

    int mid = size(v) / 2;
    auto subSol1 = optimal_cost(vector<Order>(begin(v), begin(v) + mid), wCap, vCap);
    auto subSol2 = optimal_cost(vector<Order>(begin(v) + mid, end(v)), wCap, vCap);

    {
        for (int i = 0; i <= wCap; ++i) {
            for (int j = 0; j <= vCap; ++j) {
                best = max(best, {subSol1[i][j].first + subSol2[wCap - i][vCap - j].first, {i, j}});
            }
        }
    }


    vector<int> solution;
    if (subSol1[best.second.first][best.second.second].second != -1) {
        int iChosen = subSol1[best.second.first][best.second.second].second;
        solution = knapsack_hirschberg(vector<Order>(begin(v), begin(v) + iChosen),
                                       best.second.first - v[iChosen].weight, best.second.second - v[iChosen].volume,
                                       mProf,
                                       trucks, offset, false);
        solution.push_back(subSol1[best.second.first][best.second.second].second + offset);
    }
    if (subSol2[wCap - best.second.first][vCap - best.second.second].second != -1) {
        int iChosen = mid + subSol2[wCap - best.second.first][vCap - best.second.second].second;
        auto subSolution = knapsack_hirschberg(vector<Order>(begin(v) + mid, begin(v) + iChosen),
                                               wCap - best.second.first - v[iChosen].weight,
                                               vCap - best.second.second - v[iChosen].volume, mProf, trucks,
                                               offset + mid,
                                               false);
        copy(begin(subSolution), end(subSolution), back_inserter(solution));
        solution.push_back(iChosen + offset);
    }

    return solution;
}

bool Knapsack::fitsInTruck(const Truck &t, const vector<int> &v, const vector<Order> &o) {
    int wCap = t.pesoMax, vCap = t.volMax;

    for (auto i: v) {
        wCap -= o[i].weight;
        vCap -= o[i].volume;
        if (wCap < 0 || vCap < 0)
            return false;
    }
    return true;
}

pair<int, int> Knapsack::getMax(const vector<Truck> &trucks) {
    int mW = INT32_MIN, mV = INT32_MIN;

    for (auto &f: trucks) {
        if (f.volMax > mV)
            mV = f.volMax;
        if (f.pesoMax > mW)
            mW = f.pesoMax;
    }
    return {mW, mV};
}



