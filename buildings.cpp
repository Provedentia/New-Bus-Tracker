#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <utility>
#include "buildings.h"
#include "tinyxml2.h"
#include "osm.h"
#include "busstops.h"
#include "busstop.h"
#include "dist.h"

#include "json.hpp"
using json = nlohmann::json;

using namespace std;
using namespace tinyxml2;


void Buildings::readMapBuildings(XMLDocument& xmldoc)
{
	XMLElement* osm = xmldoc.FirstChildElement("osm");
	XMLElement* way = osm->FirstChildElement("way");
	while (way != nullptr)
	{
		if (osmContainsKeyValue(way, "building", "university"))
		{
			long long building_id = stoll(way->Attribute("id"));
			string name = osmGetKeyValue(way, "name");
			string streetAddr = osmGetKeyValue(way, "addr:housenumber") + " " + osmGetKeyValue(way, "addr:street");
			
			//(void)building_id;
		
			Building building(building_id, name, streetAddr);
			
			XMLElement* nd = way->FirstChildElement("nd");
			while (nd != nullptr)
			{
				const XMLAttribute* ndref = nd->FindAttribute("ref");
				assert(ndref != nullptr);
				long long id = ndref->Int64Value();
				building.add(id);
				nd = nd->NextSiblingElement("nd");
			}
			MapBuildings.push_back(building);
		}
		way = way->NextSiblingElement("way");
		
	}
}

void Buildings::print(std::ostream& os)
{
    for (Building building : MapBuildings)
    {
        os << building.getID() << ": " << building.getName() << ", " << building.getStreetAddress() << endl;
    }
}

void Buildings::findAndPrint(string NameInput, const Nodes& nodes, const BusStops& busStops, CURL* curl, std::ostream& os)
{
    bool checker = true;
    for (Building building : MapBuildings)
    {
        if (building.getName().find(NameInput) != string::npos)
        {
            building.print(nodes, os);  // Pass the output stream to the Building's print function
            pair<BusStop, BusStop> stops = building.closestStop(busStops, nodes);
            pair<double, double> location = building.getLocation(nodes);

            os << "Closest southbound bus stop:\n  ";
            stops.second.printclosest(distBetween2Points(stops.second.getLat(), stops.second.getLon(), location.first, location.second), os);
            stops.second.printBusPredictions(curl, os);
            os << "Closest northbound bus stop:\n  ";
            stops.first.printclosest(distBetween2Points(stops.first.getLat(), stops.first.getLon(), location.first, location.second), os);
            stops.first.printBusPredictions(curl, os);
            checker = false;  // Checks if a building was found
        }
    }
    if (checker)  // Checks if the loop ever found a building
    {
        os << "No such building\n";
    }
}

int Buildings::getNumMapBuildings()
{
	return MapBuildings.size();
}

vector<Building> Buildings::getMapBuildings() const
{
	return MapBuildings;
}


