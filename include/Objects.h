#ifndef DA_T1_OBJECTS_H
#define DA_T1_OBJECTS_H

#include <iostream>
#include <vector>

using namespace std;

/**
 * struct for the storing of Truck characteristic attributes
 */
struct Truck {
    int id, volMax, pesoMax, cost;
};

/**
 * struct for the storing of Order characteristic attributes
 */
struct Order {
    int id, volume, weight, reward, duration;
};

/**
 * Compares if two Orders are the same (have same id)
 * @param l left compared Order
 * @param r right compared Order
 * @return boolean telling if Orders have same id
 */
inline bool operator==(const Order &l, const Order &r) {
    return l.id == r.id;
}

/**
 * Compares if two Trucks are the same (have same id)
 * @param l left compared Truck
 * @param r right compared Truck
 * @return boolean telling if Trucks have same id
 */
inline bool operator==(const Truck &l, const Truck &r) {
    return l.id == r.id;
}

/**
 * Compares if left Order is smaller than right Order (by the int ids)
 * @param l left compared Order
 * @param r right compared Order
 * @return boolean telling if left Order is smaller than right Order
 */
inline bool operator<(const Order &l, const Order &r) {
    return l.id < r.id;
}

/**
 * Compares if left Truck is smaller than right Truck (by the int ids)
 * @param l left compared Truck
 * @param r right compared Truck
 * @return boolean telling if left Truck is smaller than right Truck
 */
inline bool operator<(const Truck &l, const Truck &r) {
    return l.id < r.id;
}

/**
 * Overload operator <<. Allows left hand side vector to receive (append) all
 * values from the right hand side vector (they have to be of same type)
 * @tparam iterable any iterable class
 * @param left vector that will be appended values
 * @param right vector with the values to be added to the other vector
 * @return
 */
template<class iterable>
vector<iterable> &operator<<(vector<iterable> &left, const vector<iterable> &right) {
    left.reserve(right.size());
    left.insert(left.end(), right.begin(), right.end());
    return left;
}

#endif //DA_T1_OBJECTS_H
