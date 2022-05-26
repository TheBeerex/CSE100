// Author: TheBeerex
// Lab_02 ~~ lab2.cpp

#include <iostream>
#include <vector>

using namespace std;

// Utility to print entire vector
void printVector(vector<int> &vect) {
    for (auto it = vect.begin(); it != vect.end(); it++) {
        cout << *it << ";";
    }
}

/*
    The intervals [start:mid] and [mid+1:end] in data are sorted.
    The function will merge both of these intervals such that the interval [start:end] in data becomes sorted
*/
void merge(vector<int>& data, int start, int mid, int end) {
	vector<int> temp;
	int i = start;
	int j = mid+1;

	// Push elements from the two "halves" of the vector to temp storage such that the two "halves" become one sorted vector
	while (i <= mid && j <= end) {
		if (data[i] <= data[j]) {
			temp.push_back(data[i]);
			i++;
		} else {
			temp.push_back(data[j]);
			j++;
		}
	}

	// Push remaining elements from the former "half" of the vector to temp storage
	while (i <= mid) {
		temp.push_back(data[i]);
		i++;
	}

	// Push remaining elements from the latter "half" of the vector
	while (j <= end) {
		temp.push_back(data[j]);
		j++;
	}

	// Copy sorted temporary vector to the original vector.
	for (int k = start; k <= end; k++)
		data[k] = temp[k - start];

}

/* 
	Sorts the given interval, [start, end], of the vector in data using mergeSort algorithm
*/
void mergeSort(vector<int> &data, int start, int end) {
    if (start >= end)
        return;
	int mid = (start + end) / 2;
	
	// Splits the vector, data, into halves, which recursively split into more halves until each "half" is of size 1.
	mergeSort(data, start, mid);
	mergeSort(data, mid + 1, end);
	// Merge the "halves" such that they are sorted from [start:end].
	merge(data, start, mid, end);
}

// Takes n integers from the user, puts them into a vector and calls mergeSort to sort. Prints resulting vector.
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
    mergeSort(inVector, 0, inVector.size()-1);

    printVector(inVector);
    
    return 1;
}