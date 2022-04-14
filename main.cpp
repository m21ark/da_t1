#include "include/menu.h"

using namespace std::chrono;
using namespace std;

int main() {


    express_scheduling_brute(read_orders("../data/e_10/e_1.txt"));

    getchar();
    //Menu::start();

    return 0;
}
