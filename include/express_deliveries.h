#ifndef DA_T1_EXPRESS_DELIVERIES_H
#define DA_T1_EXPRESS_DELIVERIES_H

#include <iostream>
#include <algorithm>
#include <cmath>
#include "read_files.h"
#include "timer.h"
#include "Memento.h"

using namespace std;

/**
 * Algorithm that chooses the best orders given to minimize
 * the overall delivery mean time using sort O(n)= N * log N
 * @param orders orders to be chosen
 */
void express_scheduling(vector<Order> orders);


/**
 * Algorithm that chooses the best orders given to minimize
 * the overall delivery mean time using sort O(n)= N^2
 * @param orders orders to be chosen
 */
void express_scheduling_bubble(vector<Order> orders);

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
void express_scheduling_print(vector<Order> &orders, unsigned qnt);

/**
 * Basic implementation of Bubble Sort algorithm for vector
 * @param v vector to be sorted (modified)
 */
void bubbleSort(vector<Order> &v);

#endif //DA_T1_EXPRESS_DELIVERIES_H
