// Author: TheBeerex
// Lab_04-2 ~ Heap Sort

#include <vector>
#include <iostream>

using namespace std;

// Utility to print entire vector
void printVector(vector<int> &vect) {
    for (auto it = vect.begin(); it != vect.end(); it++) {
        cout << *it << ";";
    }
}


// To heapify a subtree rooted with node i which is an index in data and length size
void maxHeapify(vector<int> &data, int size, int i) {
    // Find largest among root, left child and right child
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // If left child is larger than root
    if (left < size && data[left] > data[largest])
        largest = left;

    // If right child is larger than largest so far
    if (right < size && data[right] > data[largest])
        largest = right;

    // If largest is not root
    if (largest != i) {
        swap(data[i], data[largest]);

        // Recursively heapify the affected sub-tree
        maxHeapify(data, size, largest);
    }
}


// Heap Sort alg
void heapSort(vector<int> &data, int size) {
    // Build max heap
    for (int i = size / 2 - 1; i >= 0; i--)
        maxHeapify(data, size, i);
    
    printVector(data);
    cout << endl;

    // One by one extract an element from heap and maxheapify on the reduced heap
    for (int i = size - 1; i > 0; i--) {
        swap(data[0], data[i]);

        // Heapify root element to get highest element at root again
        maxHeapify(data, i, 0);
    }
}


// Takes n integers from the user, puts them into a vector and calls heapSort. Prints resulting output.
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
    heapSort(inVector, n);

    printVector(inVector);
}