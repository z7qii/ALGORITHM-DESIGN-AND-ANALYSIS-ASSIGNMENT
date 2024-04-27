#include <iostream>
#include "../../question1/dataSet1/dataSet1.cpp"
#include <chrono>
using namespace std;

void printArray(int A[], int n)
{
    for (int i = 0; i < n; i++)
        cout << A[i] << " ";
    cout << endl;
}

void heapify(int A[], int arraySize, int j)
{
    int max;
    int left = 2 * j + 1;
    int right = 2 * j + 2;
    if (left < arraySize && A[left] > A[j])
        max = left;
    else
        max = j;
    if (right < arraySize && A[right] > A[max])
        max = right;
    if (max != j)
    {
        swap(A[j], A[max]);
        heapify(A, arraySize, max);
    }
}
void heapSort(int A[], int arraySize)
{
    for (int j = (arraySize - 1) / 2; j >= 0; j--)
        heapify(A, arraySize, j);
    for (int i = arraySize - 1; i >= 1; i--)
    {
        swap(A[0], A[i]);
        heapify(A, --arraySize, 0);
    }
}
int main()
{

    // Set the random seed reference
    unsigned int seedReference = 1211306080;

    // Create a generator with the given seed reference
    RandomDataSetGenerator generator(seedReference);

    // Generate datasets for different sizes
    int size = 100;
    int set1[size];
    generator.generateDataSet(set1, size);

    // Display the generated dataset
    cout << "Set 1 (Before sorting) :"
         << "\n\n";
    printArray(set1, size);

    // sort the generated dataset

    // Start recording the time
    auto start = std::chrono::high_resolution_clock::now();

    // Sort the generated dataset
    heapSort(set1, size);

    // Stop recording the time
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    // Display the time taken for sorting
    std::cout << "\n\nTime taken for sorting: " << duration.count() << " microseconds\n";

    // display the generated dataset after sorting
    cout << "\n\n"
         << "set 1 (After sorting) :"
         << "\n\n";
    printArray(set1, size);

    // you could do the same for all of the other datsets (dataset 2 , dataset 3 , dataset 4)
}
