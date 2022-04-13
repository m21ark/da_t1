#ifndef DA_T1_OBJECTS_H
#define DA_T1_OBJECTS_H

struct Truck {
    int id, volMax, pesoMax, cost;
};

struct Order {
    int id, volume, weight, reward, duration;
};

inline bool operator==(const Order& l,const Order& r) {
    return l.id == r.id;
}

inline bool operator<(const Order& l,const Order& r) {
    return l.id < r.id;
}

inline bool operator==(const Truck& l,const Truck& r) {
    return l.id == r.id;
}

inline bool operator<(const Truck& l,const Truck& r) {
    return l.id < r.id;
}

#endif //DA_T1_OBJECTS_H
