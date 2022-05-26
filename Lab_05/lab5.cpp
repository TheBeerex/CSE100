// Author: TheBeerex
// Lab_05 ~~ lab5.cpp

#include <iostream>
#include <string>

using namespace std;

// Utility to print array
void printArr(int* arr, int size) {
	for (int i = 0; i < size; i++) {
		cout << arr[i] << ";";
	}
}

// Utility to print 2D array
void print2DArr(int** arr, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
		printArr(arr[i], columns);
		cout << endl;
	}
}


// Radix Sort algorithm using Counting Sort
void radixSort(int** arr, int rows, int columns){

	for (int i = columns-1; i >= 0; i--) {
		/*
			Sort each row with respect to the ith column using Counting Sort.
		*/
		int** output = new int*[rows]; // output array
		int j;
		int count[4] = { 0, 0, 0, 0 };

		// Store count of occurrences in count[]
		for (j = 0; j < rows; j++)
			count[ arr[j][i] ]++;

		// Change count[j] so that count[j] now contains actual position of this digit in output[]
		for (j = 1; j < 4; j++)
			count[j] += count[j - 1];

		// Build the output array
		for (j = rows - 1; j >= 0; j--) {
			output[ count[ arr[j][i] ] - 1 ] = arr[j];
			count[ arr[j][i] ]--;
		}

		// Copy the output array to arr[], 
		//   so that arr[] now contains sorted vectors with respect to the current digit
		for (j = 0; j < rows; j++)
			arr[j] = output[j];

		delete[] output;
	}
}


// Takes n vectors of size 10 from the user (range of elements assumed to be [0:3]), 
//   puts them into a 2d array and calls radixSort to sort. Prints resulting 2d array.
int main() {	
	int** arr;
    int n;

    cin >> n;

    if (n > 0) {
		//2D int array n x 10 size
        arr = new int*[n];
		
		string temp;
		getline(cin, temp);

		for (int i = 0; i < n; i++){
			arr[i] = new int[10];
			getline(cin, temp); // i.e.: "1 3 0 0 2 2 0 0 0 0"
			for (int j = 0; j < 10; j++) {
				arr[i][j] = (int)(temp[j*2] - 48);
			}
		}

		radixSort(arr, n, 10);

		print2DArr(arr, n, 10);    
    }

    delete[] arr;

    return 1;
}