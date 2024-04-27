#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <unordered_set>
#include "../../question1/DataSet2/DataSet2.cpp"
// #include "../../question1/DataSet2/Graph.cpp"
#define INF 0x3f3f3f3f
using namespace std;

class RouteComparator
{
public:
    bool operator()(const Route &route1, const Route &route2)
    {
        return route1.distance > route2.distance;
    }
};

// Function to find the shortest paths from a source station to all other stations
// using Dijkstra's algorithm

vector<int> findShortestPaths(int srcStation, Graph &graph, int (&parent)[])
{
    // Get the number of stations in the graph
    int numOfStations = graph.getNumOfStations();

    // Priority queue to store routes based on their distances
    // RouteComparator is a custom comparator to prioritize routes with shorter distances
    priority_queue<Route, vector<Route>, RouteComparator> pq;

    // Vector to store distances from the source station to all other stations
    vector<int> distances(numOfStations, INF);

    // Set to keep track of visited stations
    unordered_set<int> visited;

    // Initialize the parent array with -1 for all stations
    parent[srcStation] = -1;

    // Push the source station into the priority queue with distance 0
    pq.push(Route(Station(srcStation), Station(srcStation), 0));

    // Set distance of source station to itself as 0
    distances[srcStation] = 0;

    // Loop until all stations are visited
    while (visited.size() < numOfStations)
    {
        // Extract the station with the minimum distance from the priority queue
        int minDistance = pq.top().dstStation.id;
        pq.pop();

        // If the station is already visited, skip it
        if (visited.count(minDistance) > 0)
            continue;

        // Get adjacent stations of the current station
        auto adjacents = graph.getAdjacents(minDistance);

        // Iterate through adjacent stations
        for (const auto &adjacent : adjacents)
        {
            int adjID = adjacent.dstStation.id;

            // Calculate new distance from source to the adjacent station through the current station
            int newDistance = distances[minDistance] + adjacent.distance;

            // If the adjacent station is not visited and the new distance is shorter
            // than the previously known distance, update the distance and add it to the priority queue
            if (visited.count(adjID) == 0 && newDistance < distances[adjID])
            {
                distances[adjID] = newDistance;
                pq.push(Route(adjacent.srcStation, adjacent.dstStation, newDistance));

                // Update parent of the adjacent stations
                parent[adjID] = minDistance;
            }
        }
        // Mark the current station as visited
        visited.insert(minDistance);
    }

    // Return the vector of distances from the source station to all other stations
    return distances;
}

char getCorrespoindingLetter(int id)
{
    if (id == -1)
        return '-';
    return 'A' + id;
}

int charToInt(char letter)
{
    // Assuming the input is a lowercase letter

    return letter - 'a';
}

int main()
{

    TreasureHuntDataSet dataSet = TreasureHuntDataSet(20, 54, "3633920568");
    Graph graph = dataSet.getDataSet();

    cout << "======================== GRAPH ======================== "
         << "\n\n";
    graph.printGraph();
    cout << "\n\n";

    char sourceStation;
    cout << "Enter source station : ";
    cin >> sourceStation;
    cout << "\n\n";

    sourceStation = tolower(sourceStation);
    int parent[graph.getNumOfStations()];
    vector<int> shortestPaths = findShortestPaths(charToInt(sourceStation), graph, parent);

    cout << "======================== shortest paths from station " << sourceStation << " ========================" << endl;

    for (int i = 0; i < shortestPaths.size(); i++)
    {
        char name = 'A' + i;
        cout << "Name: " << name << ", Shortest distance is " << shortestPaths[i] << ", ";
        cout << "Shortest path : ";
        int j = parent[i];
        string path = "";
        path += getCorrespoindingLetter(i);
        while (j != -1)
        {
            char parentName = getCorrespoindingLetter(j);
            string arrow = "=>";
            string newP = parentName + arrow;
            path = newP + path;
            j = parent[j];
        }
        cout << path << "\n";
    }

    cout << "\n\n\n\n\n";
    cout << "======================== Graph representing the shortest paths ========================";
    cout << "\n";
    for (int i = 0; i < graph.getNumOfStations(); i++)
    {
        cout << getCorrespoindingLetter(i) << ", parent => " << getCorrespoindingLetter(parent[i]) << "\n";
    }
}