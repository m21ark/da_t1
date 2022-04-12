#ifndef DA_T1_READ_FILES_H
#define DA_T1_READ_FILES_H

#include "Objects.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

bool file_exists(const string &path);

vector<Truck> read_trucks(const string &path);

vector<Order> read_orders(const string &path);

ostream &operator<<(ostream &os, const Truck &l);

ostream &operator<<(ostream &os, const Order &l);

istream &operator>>(istream &is, Truck &l);

istream &operator>>(istream &is, Order &l);


#endif //DA_T1_READ_FILES_H
