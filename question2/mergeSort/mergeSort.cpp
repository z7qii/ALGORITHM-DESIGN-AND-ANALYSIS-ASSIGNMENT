
#include <iostream>
#include <vector>
#include "../../question1/dataSet1/dataSet1.cpp"
#include <chrono>
#include <bits/stdc++.h>
using namespace std;

void merge(int array[], int const left, int const mid,
           int const right)
{
    int const subArrayOne = mid - left + 1;
    int const subArrayTwo = right - mid;

    auto *leftArray = new int[subArrayOne],
         *rightArray = new int[subArrayTwo];

    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];

    auto indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;

    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo)
    {
        if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo])
        {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else
        {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }

    while (indexOfSubArrayOne < subArrayOne)
    {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }

    while (indexOfSubArrayTwo < subArrayTwo)
    {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
    delete[] leftArray;
    delete[] rightArray;
}

void mergeSort(int array[], int const begin, int const end)
{
    if (begin >= end)
        return;

    int mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}

void printArray(int A[], int size)
{
    for (int i = 0; i < size; i++)
        cout << A[i] << " ";
    cout << endl;
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
    mergeSort(set1, 0, size - 1);

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
