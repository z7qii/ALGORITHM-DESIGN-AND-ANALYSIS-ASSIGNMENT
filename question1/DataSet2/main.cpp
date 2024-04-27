#include "DataSet2.cpp"
#include <iomanip>

template <typename Container>
void printStations(const Container &stations)
{
     cout << "===================================================================================="
          << "\n";
     cout << "||    Station    ||    x    ||    y    ||    z    ||    Weight    ||    Profit    ||"
          << "\n";
     cout << "===================================================================================="
          << "\n";

     for (const auto &station : stations)
     {
          int xLength = to_string(station.x).length();
          int yLength = to_string(station.y).length();
          int zLength = to_string(station.z).length();
          int weightLength = to_string(station.weight).length();
          int profitLength = to_string(station.profit).length();

          cout
              << "||    "
              << "Station " << station.name << "  ||    " << station.x << setw(11 - xLength) << "||    " << station.y << setw(11 - yLength) << "||    " << station.z << setw(11 - zLength) << "||    " << station.weight << setw(16 - weightLength) << "||    " << station.profit << setw(12 - profitLength) << "||"
              << "\n";

          cout << "===================================================================================="
               << "\n";
     }
}

int calculateDistance(Station stationX, Station stationY)
{
     double power = 2.0;
     double arg1 = stationY.x - stationX.x;
     double arg2 = stationY.y - stationX.y;
     double arg3 = stationY.z - stationX.z;

     int distance = sqrt(pow(arg1, power) + pow(arg2, power) + pow(arg3, power));
     return distance;
}

int main()
{

     TreasureHuntDataSet dataSet = TreasureHuntDataSet(20, 54, "3633920568");
     vector<Station> stations = dataSet.getStations();

     cout << "\n\n";
     cout << "===================================== STATIONS ====================================="
          << "\n\n";
     printStations(stations);

     cout << "\n\n";
     cout << "===================================== GENERATED GRAPH ====================================="
          << "\n\n";

     dataSet.printDataSet();
}