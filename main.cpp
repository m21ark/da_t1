#include "include/menu.h"

using namespace std::chrono;
using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


vector<vector<pair<int, int>>> optimal_cost(vector<Order> const& v, int wCap, int vCap) {
    vector<vector<pair<int, int>>> dp(wCap + 1, vector<pair<int,int>>(vCap + 1,{ 0, -1 }));

    for (int i = 0; i < size(v); ++i) {
        for (int j = wCap; j >= 0; --j) {
            for (int k = vCap; k >= 0 ; --k) {
                if (v[i].weight <= j && v[i].volume <= k
                && dp[j][k].first < dp[j - v[i].weight][k - v[i].volume].first + v[i].reward
                ) {
                    dp[j][k] = { dp[j - v[i].weight][k - v[i].volume].first + v[i].reward, i };
                }
            }
        }
    }

    return dp;
}


//adaptado de https://stackoverflow.com/questions/36834028/reconstructing-the-list-of-items-from-a-space-optimized-0-1-knapsack-implementat
vector<int> knapsack_hirschberg(const vector<Order> & v,  int wCap, int vCap, int offset = 0) {
    if (empty(v)) {
        return {};
    }

    int mid = size(v) / 2;
    auto subSol1 = optimal_cost(vector<Order>(begin(v), begin(v) + mid), wCap, vCap);
    auto subSol2 = optimal_cost(vector<Order>(begin(v) + mid, end(v)), wCap, vCap);

    pair<int, pair<int,int>> best = { -1, {-1,-1} };
    for (int i = 0; i <= wCap; ++i) {
        for (int j = 0; j <= vCap; ++j) {
            best = max(best, { subSol1[i][j].first + subSol2[wCap - i][vCap - j].first, {i,j} });
        }
    }
    /*
     * MAYBE WE CAN BUILD A BETTER SOLUTION BASED ON THE ABOVE, separating this part of the code for another one
     */

    vector<int> solution;
    if (subSol1[best.second.first][best.second.second].second != -1) {
        int iChosen = subSol1[best.second.first][best.second.second].second;
        solution = knapsack_hirschberg(vector<Order>(begin(v), begin(v) + iChosen),
                best.second.first - v[iChosen].weight, best.second.second - v[iChosen].volume,offset);
        solution.push_back(subSol1[best.second.first][best.second.second].second + offset);
    }
    if (subSol2[wCap - best.second.first][vCap - best.second.second].second != -1) {
        int iChosen = mid + subSol2[wCap - best.second.first][vCap - best.second.second].second;
        auto subSolution = knapsack_hirschberg(vector<Order>(begin(v) + mid, begin(v) + iChosen),
                wCap - best.second.first - v[iChosen].weight, vCap - best.second.second - v[iChosen].volume,offset + mid);
        copy(begin(subSolution), end(subSolution), back_inserter(solution));
        solution.push_back(iChosen + offset);
    }

    return solution;
}

bool fitsInTruck(const Truck& t,const vector<int>& v, const vector<Order>& o) {

    int wCap = t.pesoMax;
    int vCap = t.volMax;

    for (auto i: v) {
        wCap -= o[i].weight;
        vCap -= o[i].volume;
        if (wCap < 0 || vCap < 0)
            return false;
    }
    return true;
}

pair<int,int> getMax(const vector<Truck> & trucks) {
    int mW = INT_MIN, mV = INT_MIN;

    int s = INT_MIN;

    for (auto& f : trucks) {
        int dens = f.pesoMax + f.volMax;
        if (dens> s) {
            mV = f.volMax;
            mW = f.pesoMax;
            s = dens;
        }
    }
    return {mW, mV};
}

int main() {

    vector<Truck> trucks = read_trucks("../data/c_50/c_1.txt");
    vector<Order> orders = read_orders("../data/e_450/e_1.txt");
    vector<int> profit;
    int total_profit=0;
    int i = orders.size();

    sort(trucks.begin(), trucks.end(), [](const Truck& l, const Truck& r){return l.cost < r.cost;});
    Timer::start();

    do {
        auto itTruckChosen = trucks.end();

        int max_prof = INT32_MIN;

        vector<Order> used_items;

        auto f = getMax(trucks);
        Timer::start();
        auto d  = knapsack_hirschberg(orders,f.first, f.second);
        /**
         * WE COULD CALL THE ABOVE FUNC EVERY TIME BUT THAT'S NOT A RAPID SOLUTION
         */

        Timer::stop();
        cout << "Time Taken: " << Timer::getTime() << "s\n";

        // O(n * k) ... just an access to a vector that counts k iterations at maximum being k ~ size of orders
        for (auto truck = trucks.begin(); truck != trucks.end(); truck++) {
            int prof = 0;

            if (!fitsInTruck(*truck,d,orders))
                continue;

            for (auto c : d) {
                prof += orders[c].reward;
            }

            if (prof > max_prof) {
                max_prof = prof - truck->cost;
                for (auto c : d) {
                    used_items.push_back(orders[c]);
                }
                itTruckChosen = truck;
            }
            break;
        }

        cout    << "OUT" << endl;

        if (max_prof <= 0)
            break;
        profit.push_back(max_prof);

        cout << "Truck_id: " << itTruckChosen->id << endl;

        if (itTruckChosen != trucks.end())
            trucks.erase(itTruckChosen);

        for (auto e: used_items) {
            auto it = std::find(orders.begin(), orders.end(), e);
            if (it != orders.end())
                orders.erase(it);
        }
        i -= used_items.size();
        cout << i << " " << used_items.size() << " " << orders.size() << " " << max_prof << " " << trucks.size()
             << endl;
    } while (i > 0 && !trucks.empty());

    Timer::stop();
    for (auto &pr: profit)
        total_profit += pr;

    cout << "Total Profit = " << total_profit << endl;
    cout << "Time Taken: " << Timer::getTime() << "s\n";
    // Menu::start();
    getchar();

    return 0;
}
