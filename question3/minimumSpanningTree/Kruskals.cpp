#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include "../../question1/DataSet2/DataSet2.cpp"

#include <bits/stdc++.h>
using namespace std;

struct node
{
    int parent;
    int rank;
};

vector<node> dsuf;

bool comparator(Route a, Route b)
{
    return a.distance < b.distance;
}

// setRoutesList
void setRoutesList(Graph graph, vector<Route> &routesList, int numOfStations)
{
    list<Route> *routes = graph.getRoutes();
    for (int i = 0; i < numOfStations; i++)
    {
        for (Route route : routes[i])
        {
            routesList.push_back(route);
        }
    }
}

void setDsuf(int numOfStations)
{
    dsuf.resize(numOfStations);             // Mark all vertices as separate subsets with only 1 element
    for (int i = 0; i < numOfStations; ++i) // Mark all nodes as independent set
    {
        dsuf[i].parent = -1;
        dsuf[i].rank = 0;
    }
}
// FIND operation
int find(int v)
{
    if (dsuf[v].parent == -1)
        return v;
    return dsuf[v].parent = find(dsuf[v].parent); // Path Compression
}

void union_op(int fromP, int toP)
{

    // UNION by RANK
    if (dsuf[fromP].rank > dsuf[toP].rank) // fromP has higher rank
        dsuf[toP].parent = fromP;
    else if (dsuf[fromP].rank < dsuf[toP].rank) // toP has higher rank
        dsuf[fromP].parent = toP;
    else
    {
        // Both have same rank and so anyone can be made as parent
        dsuf[fromP].parent = toP;
        dsuf[toP].rank += 1; // Increase rank of parent
    }
}

int findMst(Graph &graph, Graph &mst)
{
    int numOfStations = graph.getNumOfStations();
    int numOfRoutes = graph.getNumOfRoutes();

    int mstCost = 0;          // keep track of minimum spanning tree cost
    vector<Route> routesList; // vector to store all the routes
    setRoutesList(graph, routesList, numOfStations);

    setDsuf(numOfStations);
    sort(routesList.begin(), routesList.end(), comparator); // sort all routes by distance

    int i = 0, j = 0;
    while (i < numOfStations - 1 && j < numOfRoutes * 2)
    {
        int fromP = find(routesList[j].srcStation.id); // FIND absolute parent of subset
        int toP = find(routesList[j].dstStation.id);   // FIND absolute parent of subset

        if (fromP == toP) // if both are equal then we would ignore this route because adding it will create a cycle
        {
            ++j;
            continue;
        }

        // UNION operation
        union_op(fromP, toP);              // UNION of 2 sets
        mst.addRoute(routesList[j]);       // add this route to the minimum spanning tree
        mstCost += routesList[j].distance; // increase the minimum spanning tree cost
        ++i;
        ++j;
    }

    return mstCost;
}
