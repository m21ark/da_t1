#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../include/read_files.h"

using testing::Eq;




TEST(test_file, test_file_read) {

    vector<Truck> trucks = read_trucks("../data/carrinhas.txt");
    vector<Order> orders = read_orders("../data/encomendas.txt");


    for (auto i: orders) {
        cout << i << endl;
    }

    cout << "\n\n\n\n\n\n";

    for (auto i: trucks) {
        cout << i << endl;
    }

    //ASSERT_EQ(1,1);
}




