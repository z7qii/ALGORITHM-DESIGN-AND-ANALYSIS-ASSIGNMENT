#include "Kruskals.cpp"
#include <iostream>

using namespace std;

char getCorrespoindingLetter(int id)
{
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

    int numOfStations = graph.getNumOfStations();
    int numOfRoutes = graph.getNumOfRoutes();

    cout << "========================== ORIGINAL GRAPH =========================="
         << "\n\n";
    graph.printGraph();
    cout << "\n\n\n\n";

    cout << "============================ MINIMUM SPANNING TREE ============================"
         << "\n\n";
    Graph mst(numOfStations, numOfRoutes);
    int mstCost = findMst(graph, mst);

    mst.printGraph();
    cout << "\n\n\n";
    cout << "MINIMUM SPANNING TREE COST : " << mstCost;

    return 0;
}