#include <iostream>
#include <list>
#include <vector>
#include <random>
#include <set>
#include <unordered_map>
using namespace std;

class Station
{
public:
    char name;
    int id;
    int x;
    int y;
    int z;
    int weight;
    int profit;
    Station(char name, int id, int x, int y, int z, int weight, int profit)
    {
        this->name = name;
        this->id = id;
        this->x = x;
        this->y = y;
        this->z = z;
        this->weight = weight;
        this->profit = profit;
    }
    Station(int weight, int profit)
    {
        this->weight = weight;
        this->profit = profit;
    }
    Station(int id)
    {
        this->id = id;
    }
    Station(char name, int id)
    {
        this->name = name;
        this->id = id;
    }
    Station() : id(0), x(0), y(0), z(0), weight(0), profit(0) {}
    ~Station() = default;
};

class Route
{
public:
    Station srcStation;
    Station dstStation;
    int distance;
    Route(Station srcStation, Station dstStation, int distance)
    {
        this->srcStation = srcStation;
        this->dstStation = dstStation;
        this->distance = distance;
    }
};

class Graph
{
    int numOfStations;
    int numOfRoutes;
    list<Route> *routes;

public:
    Graph(int numOfStations, int numOfRoutes)
    {
        this->numOfStations = numOfStations;
        this->numOfRoutes = numOfRoutes;
        routes = new list<Route>[numOfStations];
    }
    Graph() {}

    int getNumOfStations()
    {
        return numOfStations;
    }

    int getNumOfRoutes()
    {
        return numOfRoutes;
    }

    void setRoutes(list<Route> *routes)
    {
        this->routes = routes;
    }
    list<Route> *getRoutes()
    {
        return routes;
    }
    bool isAdjacent(int xId, int yId)
    {
        list<Route> adjacents = routes[xId];
        for (Route adjacent : adjacents)
        {
            if (adjacent.dstStation.id == yId)
                return true;
        }
        return false;
    }

    void addRoute(Route route)
    {
        routes[route.srcStation.id].push_back(route);
        routes[route.dstStation.id].push_back(Route(route.dstStation, route.srcStation, route.distance));
    }

    int getNumOfAdjacents(int vertixId)
    {
        return routes[vertixId].size();
    }

    int getDistance(int srcID, int dstID)
    {
        list<Route> adjacents = routes[srcID];
        for (Route route : adjacents)
        {
            if (route.dstStation.id == dstID)
                return route.distance;
        }
        return numeric_limits<int>::max();
    }

    list<Route> getAdjacents(int srcID)
    {
        return routes[srcID];
    }

    void printGraph()
    {

        for (int i = 0; i < numOfStations; i++)
        {
            char name = 'A' + i;
            cout << "Station " << name << "--->";
            int j = 0;
            for (Route x : routes[i])
            {
                cout << "[ " << x.dstStation.name << " - " << x.distance << "]";
                j++;
                if (j < routes[i].size())
                    cout << "--->";
            }

            cout << endl;
            cout << endl;
        }
    }
};
