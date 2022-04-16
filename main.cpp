#include "include/menu.h"

using namespace std::chrono;
using namespace std;

#include <vector>
#include <algorithm>

using namespace std;

int main() {

    vector<Truck> trucks = read_trucks("../data/c_50/c_1.txt");
    vector<Order> orders = read_orders("../data/e_450/e_1.txt");

   OptimizeProfit::greedyTrucksAndOptimizedSpaceOfLK(trucks, orders);
    getchar();

    Menu::start();
   getchar();

   return 0;
}
