#include <string>
#include "curl_util.h"

#pragma once
using namespace std;
 //
//singular Bus Stop object with the given parameters, an id, the route number,
//the name of the stop, the direction it is going in, the relational location, and the latitude and longitudes.
//
class BusStop
{
    int ID;
    int Route;
    string StopName;
    string Direction;
    string Location;
    double Lat;
    double Lon;

public:

    //
    //default constructor
    //
    BusStop();
   
    BusStop(int id, int route, string stopname, string direction, string location, double lat, double lon);
    // get the ID
    int getID() const;
    // gets the Direction
    string getDirection();
    // gets the Route
    int getRoute();
    //gets the latitude
    double getLat();
    //gets the longitude
    double getLon();
    //prints the bus stop using cout
    void print(ostream& os);
    //prints the closest bus stop when given a distance
    void printclosest(double distance, ostream& os);
    //useing the CTA api prints the bus prediction
    void printBusPredictions(CURL* curl, ostream& os);
};

