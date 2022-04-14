#ifndef DA_T1_EXPRESS_DELIVERIES_H
#define DA_T1_EXPRESS_DELIVERIES_H

#include <iostream>
#include <algorithm>
#include <cmath>
#include "read_files.h"
#include "../include/timer.h"


using namespace std;

void express_scheduling(vector<Order> orders);

void express_scheduling_brute(vector<Order> orders);

void express_scheduling_print(const vector<Order> &orders, unsigned qnt);


#endif //DA_T1_EXPRESS_DELIVERIES_H
