#include "busstops.h"
#include "busstop.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream> 

using namespace std;

//
//implementaions of the Bus Stops class with the logic of how to parse the txt file, print functions, and functions to sort, get the size, and get the vector itself.
//


BusStops::BusStops(const string& filename) 
{
    ifstream infile(filename);
    if (!infile) {
        throw runtime_error("Unable to open file: " + filename);
    }

    string line;
    while (getline(infile, line)) {
        stringstream parser(line);
        string id_str, route_str, stopname, direction, location, lat_str, lon_str;

        getline(parser, id_str, ',');
        getline(parser, route_str, ',');
        getline(parser, stopname, ',');
        getline(parser, direction, ',');
        getline(parser, location, ',');
        getline(parser, lat_str, ',');
        getline(parser, lon_str);

        int id = stoi(id_str);
        int route = stoi(route_str);
        double lat = stod(lat_str);
        double lon = stod(lon_str);

        BusStop busstop(id, route, stopname, direction, location, lat, lon);

        allBusStops.push_back(busstop);
    }
}
//prints the bus stops in the allBusStops vector
void BusStops::print(std::ostream& os)
{
    BusStops::sortAllStops();
    for (BusStop busStop : allBusStops)
    {
        busStop.print(os);  // Pass the output stream to the BusStop's print function
    }
}
//sorts allBusStops vector
void BusStops::sortAllStops()
{
    sort(allBusStops.begin(), allBusStops.end(),
         [](BusStop& s1, BusStop& s2) {return s1.getID() < s2.getID();});
}
//getter/accesor
vector<BusStop> BusStops::getAllBusStops() const
{
    return allBusStops;
}

int BusStops::numBusStops()
{
    return allBusStops.size();
}