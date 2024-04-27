#include <iostream>
#include <list>
#include <vector>
#include <random>
using namespace std;

class RandomDataSetGenerator
{
public:
    RandomDataSetGenerator(unsigned int seed) : generator(seed) {}

    void generateDataSet(int dataSet[], int size)
    {

        uniform_int_distribution<int> distribution(1, size);

        for (int i = 0; i < size; ++i)
        {
            dataSet[i] = (distribution(generator));
        }
    }

private:
    default_random_engine generator;
};
