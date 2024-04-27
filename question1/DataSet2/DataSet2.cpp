#include <iostream>
#include <list>
#include <vector>
#include <random>
#include <set>
#include <unordered_map>
#include "Graph.cpp"
using namespace std;

class TreasureHuntDataSet
{
private:
    Graph graph;
    vector<Station> stations;
    int numOfStations;
    int numOfRoutes;
    string groupIdsSum;

public:
    vector<Station> getStations()
    {
        return stations;
    }
    TreasureHuntDataSet(int numOfStations, int numOfRoutes, string groupIdsSum)
    {
        this->numOfStations = numOfStations;
        this->numOfRoutes = numOfRoutes;
        this->groupIdsSum = groupIdsSum;
        graph = Graph(numOfStations, numOfRoutes);

        initializeStations();
        generateDataSet();
    }

    // Function to add a route between two stations
    void addRoute(Station x, unordered_map<int, vector<Station>> &candidates)
    {
        int stationYIndex = getRandomIndex(candidates[x.id].size());
        Station y = candidates[x.id][stationYIndex]; // get random station to create a route with Station x
        int distance = calculateDistance(x, y);

        graph.addRoute(Route(x, y, distance));
        // Update candidates list to avoid choosing the same station again
        removeFromCandidates(candidates[x.id], stationYIndex);
        removeFromCandidates(candidates[y.id], getIndexById(candidates[y.id], x.id));
    }

    // Function to design the dataset
    void generateDataSet()
    {

        unordered_map<int, vector<Station>> candidates; // the key represent the station id and the vector<Station> is the list that the key station is allowed to choose from to create a new route
        initializeCandidates(candidates);
        int routesCounter = 0;
        // Ensure each station has at least 3 connections
        for (int i = 0; i < numOfStations; i++)
        {
            int numOfAdjacents = graph.getNumOfAdjacents(stations[i].id);

            for (int j = numOfAdjacents; j < 3; j++, routesCounter++)
                addRoute(stations[i], candidates);
        }

        // Add the remaining routes
        for (int i = 0; routesCounter < numOfRoutes; routesCounter++, i++)
            addRoute(stations[i % numOfStations], candidates);
    }

    // Function to print the dataset

    void printDataSet()
    {
        graph.printGraph();
    }

    Graph getDataSet()
    {
        return graph;
    }

private:
    // Function to initialize the candidates map
    void initializeCandidates(unordered_map<int, vector<Station>> &candidates)
    {
        for (int i = 0; i < numOfStations; ++i)
        {
            candidates[stations[i].id] = stations;
            removeFromCandidates(candidates[stations[i].id], i); // Remove the station itself from the candidates
        }
    }

    // Function to remove an element from a vector
    void removeFromCandidates(vector<Station> &candidates, int indexToRemove)
    {
        swap(candidates[indexToRemove], candidates.back());
        candidates.pop_back();
    }

    // Function to get the index of a station in a vector by its ID
    int getIndexById(vector<Station> &stations, int id)
    {
        for (int i = 0; i < stations.size(); ++i)
        {
            if (stations[i].id == id)
                return i;
        }
        return -1;
    }

    // Function to calculate the distance between two stations
    int calculateDistance(Station stationX, Station stationY)
    {
        double power = 2.0;
        double arg1 = stationY.x - stationX.x;
        double arg2 = stationY.y - stationX.y;
        double arg3 = stationY.z - stationX.z;

        int distance = sqrt(pow(arg1, power) + pow(arg2, power) + pow(arg3, power));
        return distance;
    }

    // Function to get a random index within a given range
    int getRandomIndex(int upperBound)
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> distribution(0, upperBound - 1);
        return distribution(gen);
    }

    // Function to get a random value based on group IDs sum
    int getRandomValueForData(int length)
    {

        string str = "";
        for (int i = 0; i < length; i++)
            str += groupIdsSum[getRandomIndex(groupIdsSum.length())];

        return stoi(str);
    }

    // Function to initialize stations with random valuess
    void initializeStations()
    {

        for (int i = 0; i < numOfStations; i++)
        {
            char name = 'A' + i;
            int id = i;
            int x = getRandomValueForData(3);
            int y = getRandomValueForData(3);
            int z = getRandomValueForData(3);
            int weight = getRandomValueForData(2);
            int profit = getRandomValueForData(2);
            stations.push_back(Station(name, id, x, y, z, weight, profit));
        }
    }
};
