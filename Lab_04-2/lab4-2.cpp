// Author: TheBeerex
// Lab_04-2 ~ Quicksort

#include <vector>
#include <iostream>
#include <random>
#include <time.h>

using namespace std;

// Utility to print entire vector
void printVector(vector<int> &vect) {
    for (auto it = vect.begin(); it != vect.end(); it++) {
        cout << *it << ";";
    }
}


// Partition function
int partition(vector<int> &data, int start, int end) {
    int temp;

    // Pick random pivot, swap with data[end]
    srand(time(NULL));
    int pivotIndex = rand() % (end-start) + start;
    int pivot = data[pivotIndex];

    swap(data[pivotIndex], data[end]);

    int i = start; // Proper location of pivot, assumed to be less than contents of interval [start:end]
    
    // Partition data about pivot, swapping items less than pivot with items greater than pivot until items less than pivot are to the left of pivot and items greater than are to the right.
    for (int j = start; j < end; j++) {
        if (data[j] < pivot) {
            swap(data[i], data[j]);

            i++;
        }
    }
    
    // Swap pivot with data[i]
    swap(data[i], data[end]);

    return i;
}


// Quick Sort alg
void quickSort(vector<int> &data, int start, int end) {
    if(start < end) {
        int partIndex = partition(data, start, end);

        quickSort(data, start, partIndex-1);
        quickSort(data, partIndex+1, end);
    }
}


// Takes n integers from the user, puts them into a vector and calls quickSort. Prints resulting output.
int main() {
    vector<int> inVector;
    int n;

    cin >> n;
    if (n > 0) {
        int temp;
        for (int i = 0; i < n; i++) {
            cin >> temp;
            inVector.push_back(temp);
        }
    }
    quickSort(inVector, 0, n-1);

    printVector(inVector);
}