#include "../include/read_files.h"

vector<Truck> read_trucks(const string &path) {

    vector<Truck> rows;
    fstream file(path, ios::in);

    if (!file) {
        cerr << "File error! File at: " << path << " was not found!\n";
        return {};
    }

    Truck fileObj = {};
    string aux;

    getline(file, aux);
    while (getline(file, aux)) {
        stringstream ss(aux);
        ss >> fileObj;

        rows.push_back(fileObj);
    }
    file.close();

    return rows;
}

vector<Order> read_orders(const string &path) {

    vector<Order> rows;
    fstream file(path, ios::in);
    if (!file) {
        cerr << "file " << path << " not found!\n";
        return {};
    }
    Order fileObj = {};
    string aux;

    getline(file, aux);
    while (getline(file, aux)) {
        stringstream ss(aux);
        ss >> fileObj;
        rows.push_back(fileObj);
    }
    file.close();
    return rows;
}

ostream &operator<<(ostream &os, const Truck &l) {
    os << l.id << " " << l.volMax << " " << l.pesoMax << " " << l.cost;
    return os;
}

ostream &operator<<(ostream &os, const Order &l) {
    os << l.id << " " << l.volume << " " << l.weight << " " << l.reward << " " << l.duration << " ";
    return os;
}


istream &operator>>(istream &is, Truck &l) {
    is >> l.id >> l.volMax >> l.pesoMax >> l.cost;
    return is;
}

istream &operator>>(istream &is, Order &l) {
    is >> l.id >> l.volume >> l.weight >> l.reward >> l.duration;
    return is;
}