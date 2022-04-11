#ifndef DA_T1_READ_FILES_H
#define DA_T1_READ_FILES_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;


struct Truck {
    int id, volMax, pesoMax, cost;
};


struct Order {
    int id, volume, weight, reward, duration;
};

inline bool operator==(const Order& l,const Order& r) {
    return l.id == r.id;
}

inline bool operator==(const Truck& l,const Truck& r) {
    return l.id == r.id;
}

inline bool operator<(const Order& l,const Order& r) {
    return l.id < r.id;
}


bool file_exists(const string &path);

vector<Truck> read_trucks(const string &path);

vector<Order> read_orders(const string &path);

ostream &operator<<(ostream &os, const Truck &l);

ostream &operator<<(ostream &os, const Order &l);

istream &operator>>(istream &is, Truck &l);

istream &operator>>(istream &is, Order &l);


#endif //DA_T1_READ_FILES_H
