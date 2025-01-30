#include "busstop.h"
#include <vector>
#include <string>

#pragma once
using namespace std;
//
//Stores all bus Stops
//
class BusStops
{
    vector<BusStop> allBusStops;

public:

//
//given a txt file creates a vector of busStops
//
    BusStops(const string& filename);

//sorts the vectors
    void sortAllStops();
//prints the bus stops in the vectors
    void print(ostream& os);
//getter/accesor
    vector<BusStop> getAllBusStops() const;
//return the size of the vector
    int numBusStops();
};