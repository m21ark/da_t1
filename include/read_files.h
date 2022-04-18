#ifndef DA_T1_READ_FILES_H
#define DA_T1_READ_FILES_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "Objects.h"

using namespace std;

/**
 * Checks whether a file exists at a given filepath
 * @param path path where to look for file existence
 * @return boolean if file was found
 */
bool file_exists(const string &path);

/**
 * Reads a given file content and assembles a vector of Trucks
 * @param path file of Trucks to be read and converted into vector
 * @return produced vector of Trucks stored at file
 */
vector<Truck> read_trucks(const string &path);

/**
 * Reads a given file content and assembles a vector of Orders
 * @param path file of Orders to be read and converted into vector
 * @return produced vector of Orders stored at file
 */
vector<Order> read_orders(const string &path);

/**
 * Prints struct Truck values
 * @param os ostream where to output
 * @param l value to be outputted
 * @return modified given ostream
 */
ostream &operator<<(ostream &os, const Truck &l);

/**
 * Prints struct Order values
 * @param os ostream where to output
 * @param l struct to be outputted
 * @return modified given ostream
 */
ostream &operator<<(ostream &os, const Order &l);

/**
 * Receives from istream the values needed
 * for struct Truck initialization
 * @param is istream to extract from
 * @param l struct that receives values from stream
 * @return modified given istream
 */
istream &operator>>(istream &is, Truck &l);

/**
 * Receives from istream the values needed
 * for struct Order initialization
 * @param is istream to extract from
 * @param l struct that receives values from stream
 * @return modified given istream
 */
istream &operator>>(istream &is, Order &l);


#endif //DA_T1_READ_FILES_H
