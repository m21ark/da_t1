#ifndef DA_T1_OBJECTS_H
#define DA_T1_OBJECTS_H

#include <ostream>
#include <iostream>
#include <vector>

using namespace std;

struct Truck {
    int id, volMax, pesoMax, cost;
};

struct Order {
    int id, volume, weight, reward, duration;
};

inline bool operator==(const Order &l, const Order &r) {
    return l.id == r.id;
}

inline bool operator==(const Truck &l, const Truck &r) {
    return l.id == r.id;
}

inline bool operator<(const Order &l, const Order &r) {
    return l.id < r.id;
}


inline bool operator<(const Truck &l, const Truck &r) {
    return l.id < r.id;
}

template<class iterable>
vector<iterable> &operator<<(vector<iterable> &left, const vector<iterable> &right) {
    left.reserve(right.size());
    left.insert(left.end(), right.begin(), right.end());
    return left;
}

template<class printable>
ostream &operator<<(ostream &out, const vector<printable> &v) {
    for (const printable &item: v)
        out << item << " ";
    out << endl;
    return out;
}

#endif //DA_T1_OBJECTS_H
