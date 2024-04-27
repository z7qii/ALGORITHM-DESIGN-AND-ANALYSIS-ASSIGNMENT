#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <stack>
#include <cctype>
#include <list>
#include "../question1/DataSet2/DataSet2.cpp"
#include <iomanip>
#include "question4.cpp"

#define INF 0x3f3f3f3f
using namespace std;

char getCorrespoindingLetter(int id)
{
    if (id == -1)
        return '-';
    return 'A' + id;
}

int charToInt(char letter)
{
    return letter - 'a';
}

void printMatrix(vector<vector<int>> &matrix)
{
    int rows = matrix.size();
    int columns = matrix[0].size();
    for (int i = 0; i < rows; i++)
    {
        cout << setw(11);
        for (int w = 0; w < columns; w++)
        {
            cout << matrix[i][w] << "  ";
        }
        cout << "\n";
    }
}

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
}

template <typename Container>
void printStations(const Container &stations)
{
    cout << "==================================================="
         << "\n";
    cout << "||    Station    ||    Weight    ||    Profit    ||"
         << "\n";
    cout << "==================================================="
         << "\n";

    for (const auto &station : stations)
    {
        int weightLength = to_string(station.weight).length();
        int profitLength = to_string(station.profit).length();

        cout
            << "||    "
            << "Station " << station.name << "  ||    " << station.weight << setw(16 - weightLength) << "||    " << station.profit << setw(12 - profitLength) << "||"
            << "\n";

        cout << "==================================================="
             << "\n";
    }
}

int main()
{

    TreasureHuntDataSet dataSet = TreasureHuntDataSet(20, 54, "3633920568");
    Graph graph = dataSet.getDataSet();
    vector<Station> stations = dataSet.getStations();

    cout << "\n\n\n\n";
    cout << "============== Graph ====================";
    cout << "\n\n";
    graph.printGraph();
    cout << "\n\n\n\n";

    int ansr[stations.size()];
    int capacity = 600;
    vector<vector<int>> matrix(stations.size() + 1, vector<int>(capacity + 1, 0));

    int maxProfit = Knapsack(stations, matrix, ansr, capacity);

    list<Station> winningStations;

    for (int i = 0; i < stations.size(); i++)
    {
        if (ansr[i] == 1)
            winningStations.push_back(stations[i]);
    }
    cout << "============== Treasure hunt project ===================="
         << "\n\n\n";

    cout << "You have these stations that you are allowd to visit :"
         << "\n";

    printStations(stations);
    cout << "\n\n\n";
    cout << "Since you can only carry " << capacity << "kg of profit, the maximu profit you can get is " << maxProfit << "\n"
         << "In order to get this maximum profit you need to visit these stations :"
         << "\n";

    printStations(winningStations);

    cout << "\n\n";

    cout << "============== resultatn matrix ==================="
         << "\n\n";

    printMatrix(matrix);

    cout << "\n\n";
    char homeStation;

    cout << "Input your home station to view the fastest path from your home station to the winning stations : ";
    cin >> homeStation;

    cout << "\n\n";
    cout << "============== Fastest path to winning stations ===================";
    cout << "\n\n";

    string path = "";
    homeStation = toupper(homeStation); //
    path += homeStation;

    while (winningStations.size())
    {
        stack<int> nextPath = findNearestStationPath(charToInt(tolower(homeStation)), graph, winningStations);
        nextPath.pop();
        while (nextPath.size())
        {
            if (nextPath.size() == 1)
                homeStation = getCorrespoindingLetter(nextPath.top());
            path += "=>";
            path += getCorrespoindingLetter(nextPath.top());
            nextPath.pop();
        }

        for (auto it = winningStations.begin(); it != winningStations.end(); ++it)
        {
            if (it->name == homeStation || it->name == tolower(homeStation))
            {
                winningStations.erase(it);
                break;
            }
        }
    }

    cout << path << "\n\n";
    cout << "============== Good luck with the treasure hunt ===================";
}