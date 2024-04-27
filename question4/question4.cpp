

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

stack<int> getPath(int parent[], int dstStation)
{
    stack<int> path;
    int i = dstStation;
    while (i != -1)
    {
        path.push(i);
        i = parent[i];
    }

    return path;
}

stack<int> findNearestStationPath(int srcStation, Graph &graph, list<Station> &dstStations)
{

    int parent[graph.getNumOfStations()];
    int numOfStations = graph.getNumOfStations();
    priority_queue<Route, vector<Route>, RouteComparator> pq;
    vector<int> distances(numOfStations, INF);
    set<int> visited;

    parent[srcStation] = -1;
    pq.push(Route(Station(srcStation), Station(srcStation), 0));
    distances[srcStation] = 0;

    set<int> dstStationsSet;
    int nearestStationID;
    for (Station s : dstStations)
        dstStationsSet.insert(s.id);

    while (visited.size() < numOfStations)
    {

        int minDistance = pq.top().dstStation.id;
        if (dstStationsSet.count(minDistance) > 0)
        {
            nearestStationID = minDistance;
            break;
        }
        pq.pop();

        if (visited.count(minDistance) > 0)
            continue;

        auto adjacents = graph.getAdjacents(minDistance);

        for (const auto &adjacent : adjacents)
        {
            int adjID = adjacent.dstStation.id;
            int newDistance = distances[minDistance] + adjacent.distance;

            if (visited.count(adjID) == 0 && newDistance < distances[adjID])
            {
                distances[adjID] = newDistance;
                pq.push(Route(adjacent.srcStation, adjacent.dstStation, newDistance));
                parent[adjID] = minDistance;
            }
        }

        visited.insert(minDistance);
    }

    return getPath(parent, nearestStationID);
}

bool compareByWeight(const Station &a, const Station &b)
{
    return a.weight < b.weight;
}

void setWinningStations(int rows, int columns, vector<vector<int>> &matrix, vector<Station> &stations, int ansr[])
{
    int n = rows - 1;                  // Total number of stations
    int i = rows - 1, w = columns - 1; // Initializing pointers for traversing the matrix
    int arri = stations.size() - 1;    // Initializing index to traverse stations vector from the end

    while (i >= 1)
    {
        // Check if the value in the current cell is equal to the value in the cell above it
        if (matrix[i][w] == matrix[i - 1][w]) // Station is not included in the optimal solution
            ansr[stations[arri].id] = 0;
        else
        {
            ansr[stations[arri].id] = 1;   // Station is included in the optimal solution
            w = w - stations[arri].weight; // Update the remaining capacity
        }

        i--;    // Move to the row above
        arri--; // Move to the previous station
    }
}

int Knapsack(vector<Station> &stations, vector<vector<int>> &matrix, int ansr[], int capacity)
{
    int rows = stations.size() + 1; // Number of rows in the matrix
    int columns = capacity + 1;     // Number of columns in the matrix

    for (int i = 0; i < columns; i++)
        matrix[0][i] = 0;

    // Iterate through each station and each possible capacity
    for (int i = 1; i < rows; i++)
    {
        for (int w = 0; w < columns; w++)
        {
            if (i == 0 || w == 0)
                matrix[i][w] = 0; // Base case: no items or no capacity left

            else if (stations[i - 1].weight > w)
                matrix[i][w] = matrix[i - 1][w]; // Cannot include the current station

            else
                matrix[i][w] = max(matrix[i - 1][w], matrix[i - 1][w - stations[i - 1].weight] + stations[i - 1].profit); // Maximum value including or excluding the current station
        }
    }

    // Determine the winning stations based on the calculated matrix
    setWinningStations(rows, columns, matrix, stations, ansr);

    // Determine the winning stations based on the calculated matrix
    int maxProfit = matrix[rows - 1][columns - 1];
    return maxProfit;
}
