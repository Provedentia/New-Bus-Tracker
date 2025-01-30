#include <iostream>
#include <string> 
#include <utility>
#include "building.h"
#include "nodes.h"
#include "node.h"
#include <cassert>
#include "busstop.h"
#include "busstops.h"
#include "dist.h"

using namespace std;

Building::Building(long long id, string name, string streetAddr)
  : ID(id), Name(name), StreetAddress(streetAddr)
{}


void Building::add(long long nodeid)
{
	NodeIDs.push_back(nodeid);
}

void Building::print(const Nodes& nodes, std::ostream& os)
{
    pair<double, double> latAndLon = Building::getLocation(nodes);
    os << Name << "\nAddress: " << StreetAddress << "\nBuilding ID: " << ID << "\n# perimeter nodes: " << NodeIDs.size() << endl;
    os << "location: (" << latAndLon.first << ", " << latAndLon.second << ")\n";
}


pair<double, double> Building::getLocation(const Nodes& nodes)
{
	double sumLat = 0.0;
	double sumLon = 0.0;
	int totalSize = 0;
	for (long long node : NodeIDs)//loop to output all the nodes
		{
			double lat, lon;
			bool isEntrance;
			if (nodes.find(node, lat, lon, isEntrance))
			{
				// assert(false);
				sumLat += lat;
				sumLon += lon;
				totalSize++;
			}
		}

	return make_pair(sumLat / totalSize, sumLon / totalSize);
}

pair<BusStop, BusStop> Building::closestStop(const BusStops& busStops, const Nodes& nodes)
{
	pair<double, double> buildingLocation = Building::getLocation(nodes);
	
	double nBoundDist = 10000000000000.0;
	double sBoundDist = 10000000000000.0;
	
	BusStop nBound;
	BusStop sBound;

	for(BusStop busStop: busStops.getAllBusStops())
	{
		string dir = busStop.getDirection();
		
		if (dir == "Northbound")
		{
			double distance = distBetween2Points(buildingLocation.first, buildingLocation.second, busStop.getLat(), busStop.getLon());
			if (distance < nBoundDist)
			{
				nBound = busStop;
				nBoundDist = distance;
			}
		}
		else if (dir == "Southbound")
		{
			double distance = distBetween2Points(buildingLocation.first, buildingLocation.second, busStop.getLat(), busStop.getLon());
			if (distance < sBoundDist)
			{
				sBound = busStop;
				sBoundDist = distance;
			}
		}
	}
	return make_pair(nBound, sBound);

}

long long Building::getID() const
{
	return ID;
}

string Building::getName() const
{
	return Name;
}
string Building::getStreetAddress() const
{
	return StreetAddress;
}
vector<long long> Building::getNodeIDs() const
{
	return NodeIDs;
}
