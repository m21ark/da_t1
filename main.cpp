#include <iostream>
#include <fstream>
#include "include/read_files.h"


using namespace std;

int main() {
    string s1, s2;
    s1 = "../data/c_5/c2.txt";
    s2 = "../data/e_5/e1.txt";
    for(auto i:read_trucks(s1)) cout<<i<<endl;
    cout<<endl;
    for(auto i:read_orders(s2)) cout<<i<<endl;

    getchar();
    return 0;
}
