/*main.cpp*/
#include <iostream>
#include <string>
#include "nodes.h"
#include "osm.h"
#include "tinyxml2.h"
#include "buildings.h"
#include "busstops.h"
#include "curl_util.h"
#include "httplib.h"

using namespace std;
using namespace tinyxml2;

int main() {
    CURL* curl = curl_easy_init();
    if (curl == nullptr) {
        cerr << "**ERROR: unable to initialize curl library" << endl;
        return -1;
    }

    string name;
    cout << "** NU open street map **\n\n";
    cout << "Enter map filename>\n";
    getline(cin, name);
    XMLDocument xmldoc;
    if (!osmLoadMapFile(name, xmldoc)) {
        cout << "** Program Terminated **\n";
        return -1;
    }

    Nodes node;
    int numNodes;
    node.readMapNodes(xmldoc);
    numNodes = node.getNumMapNodes();

    Buildings buildings;
    int numBuildings;
    buildings.readMapBuildings(xmldoc);
    vector<Building> mapBuildings = buildings.getMapBuildings();
    numBuildings = buildings.getNumMapBuildings();

    string fileName = "bus-stops.txt";
    BusStops busStops(fileName);

    // Set up the HTTP server
    httplib::Server svr;

    // Endpoint to get the number of nodes, buildings, and bus stops
    svr.Get("/info", [&](const httplib::Request& req, httplib::Response& res) {
        res.set_content("{\"nodes\": " + to_string(numNodes) + 
                        ", \"buildings\": " + to_string(numBuildings) + 
                        ", \"bus_stops\": " + to_string(busStops.numBusStops()) + "}", "application/json");
    });

    // Endpoint to list all buildings
    svr.Get("/buildings", [&](const httplib::Request& req, httplib::Response& res) {
        stringstream ss;
        buildings.print(ss);
        res.set_content(ss.str(), "text/plain");
    });

    // Endpoint to list all bus stops
    svr.Get("/bus-stops", [&](const httplib::Request& req, httplib::Response& res) {
        stringstream ss;
        busStops.print(ss);
        res.set_content(ss.str(), "text/plain");
    });

    // Endpoint to search for a building and get information
    svr.Get("/search", [&](const httplib::Request& req, httplib::Response& res) {
        string nameInput = req.get_param_value("name");
        if (nameInput.empty()) {
            res.set_content("{\"error\": \"No name provided\"}", "application/json");
            return;
        }
        stringstream ss;
        buildings.findAndPrint(nameInput, node, busStops, curl, ss);
        res.set_content(ss.str(), "text/plain");
    });

    cout << "Server started at http://localhost:8080\n";
    svr.listen("localhost", 8080);

    curl_easy_cleanup(curl);
    return 0;
} 