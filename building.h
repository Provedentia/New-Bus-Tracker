/*building.h*/

//
// A building in the Open Street Map.
// 
// Prof. Joe Hummel, Prof. Yiji Zhang
// Northwestern University
// CS 211
// 

#pragma once

#include <string>
#include <vector>
#include <utility>

#include "node.h"
#include "nodes.h"
#include "busstop.h"
#include "busstops.h"

using namespace std;


//
// Building
//
// Defines a campus building with a name (e.g. "Mudd"), a street
// address (e.g. "2233 Tech Dr"), and the IDs of the nodes that
// define the position / outline of the building.
// 
// NOTE: the Name could be empty "", the HouseNumber could be
// empty, and the Street could be empty. Imperfect data.
//
class Building
{

  long long ID;
  string Name;
  string StreetAddress;
  vector<long long> NodeIDs;

public:
  //
  // constructor
  //
  Building(long long id, string name, string streetAddr);

  //
  // adds the given nodeid to the end of the vector.
  //
  void print(const Nodes& nodes, ostream& os);

  pair<double, double> getLocation(const Nodes& nodes);

  pair<BusStop, BusStop> closestStop(const BusStops& busStops, const Nodes& nodes);

  Nodes getNodes();

  void add(long long nodeid);

  //
  // accessor
  // 
  long long getID() const;
  string getName() const;
  string getStreetAddress() const;
  vector<long long> getNodeIDs() const;

};
