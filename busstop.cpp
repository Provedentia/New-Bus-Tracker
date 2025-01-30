#include <string>
#include <iostream>
#include "busstop.h"
#include "curl_util.h"
#include "json.hpp"
using json = nlohmann::json;

using namespace std;
//
//Implementation of the bus stop class 
// consists of getters and print functions
BusStop::BusStop() 
        :ID(0), Route(0), StopName("Unknown"), Direction("Unknown"), 
          Location("Unknown"), Lat(0.0), Lon(0.0) {}

BusStop::BusStop(int id, int route, string stopname, string direction, string location, double lat, double lon)
 :ID(id), Route(route), StopName(stopname), Direction(direction), Location(location), Lat(lat), Lon(lon)
 {}
//
//getters/accesors
//

int BusStop::getID() const 
{
    return ID;
}

string BusStop::getDirection()
{
    return Direction;
}

int BusStop::getRoute()
{
    return Route;
}

double BusStop::getLat()
{
    return Lat;
}

double BusStop::getLon()
{
    return Lon;
}
//print functions
void BusStop::print(std::ostream& os)
{
    os << ID << ": bus " << Route << ", " << StopName << ", " << Direction << ", " << Location << ", location (" << Lat << ", " << Lon << ")" << endl;
}

void BusStop::printclosest(double distance, std::ostream& os)
{
    os << ID << ": " << StopName << ", bus #" << Route << ", " << Location << ", " << distance << " miles" << endl;
}

void BusStop::printBusPredictions(CURL* curl, std::ostream& os)
{
    string url1 = "http://ctabustracker.com/bustime/api/v2/getpredictions?key=eHKQ7GBZLW5ZhjcVpzVpby3BW&rt=";
    string route = to_string(Route);
    string url2 = "&stpid=";
    string id = to_string(ID);
    string url3 = "&format=json";
    string API = url1 + route + url2 + id + url3;
    string Response;

    if (callWebServer(curl, API, Response))
    {
        auto jsondata = json::parse(Response);
        auto bus_response = jsondata["bustime-response"];
        auto predictions = bus_response["prd"];
        if (predictions.empty())
        {
            os << "  <<No predictions available>>" << endl;
        }
        else
        {
            for (auto& M : predictions)
            {
                try
                {
                    os << "  vehicle #" << stoi(M["vid"].get_ref<std::string&>());
                    os << " on route " << M["rt"].get_ref<std::string&>();
                    os << " travelling " << M["rtdir"].get_ref<std::string&>();
                    os << " to arrive in " << M["prdctdn"].get_ref<std::string&>() << " mins" << endl;
                }
                catch (exception& e)
                {
                    os << " error" << endl;
                    os << " malformed CTA response, prediction unavailable"
                       << " (error: " << e.what() << ")" << endl;
                }
            }
        }
    }
    else
    {
        os << "<bus predictions unavailable, call failed>>" << endl;
    }
}