#ifndef DA_T1_EXPRESS_DELIVERIES_H
#define DA_T1_EXPRESS_DELIVERIES_H

#include <iostream>
#include <algorithm>
#include <cmath>
#include "read_files.h"
#include "../include/timer.h"

using namespace std;

/**
 * Algorithm that chooses the best orders given to minimize
 * the overall delivery mean time
 * @param orders orders to be chosen
 */
void express_scheduling(vector<Order> orders);

/**
 * Algorithm that brute-forces all given order combinations
 * to minimize the overall delivery mean time
 * @param orders
 */
void express_scheduling_brute(vector<Order> orders);

/**
 * Prints to the screen the orders chosen to be delivered
 * @param orders vector with all orders possible
 * @param qnt number of orders to be delivered
 */
void express_scheduling_print(const vector<Order> &orders, unsigned qnt);

#endif //DA_T1_EXPRESS_DELIVERIES_H
