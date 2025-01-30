/*buildings.h*/

//
// A collection of buildings in the Open Street Map.
// 
// Prof. Joe Hummel
// Northwestern University
// CS 211: Winter 2023
// 

#pragma once 

#include <vector>

#include "building.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;


//
// Keeps track of all the buildings in the map.
//
class Buildings
{

  vector<Building> MapBuildings;

public:
  //
  // readMapBuildings
  //
  // Given an XML document, reads through the document and 
  // stores all the buildings into the given vector.
  //
  void readMapBuildings(XMLDocument& xmldoc);

  void print(ostream& os);

  void findAndPrint(string NameInput, const Nodes& nodes, const BusStops& busStops,CURL* curl, ostream& os);
  //
  // accessors / getters
  //
  int getNumMapBuildings();
  vector<Building> getMapBuildings() const;
};


