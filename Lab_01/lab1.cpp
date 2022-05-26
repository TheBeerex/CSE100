// Author: TheBeerex
// Lab_01 ~~ lab1.cpp

#include <iostream>
#include <vector>
#include <algorithm> // for rotate() and upper_bound() functions

using namespace std;

// Utility to print entire vector
void printVector(vector<int> &vect) {
    for (auto it = vect.begin(); it != vect.end(); it++) {
        cout << *it << ";";
    }
    cout << endl;
}

// Utility to print first k elements where 2 <= k <= vect.size()
void printKElements(vector<int> &vect, int k) {
    if (k >= 2){
        for (int i = 0; i < vect.size() && i < k; i++) {
            cout << vect[i] << ";";
        }
        cout << endl;
    }
}

// Insertion Sort Algorithm
void insertionSort(vector<int> &data) {
    vector<int>::iterator it;
    int counter = 0;
    for (it = data.begin(); it != data.end(); it++) {
        /* 
        upper_bound(data.begin(), it, *it) finds the "highest" point which a value (*it) 
            can be placed that doesn't change the order (ascending) within the interval [data.begin(),it]
                ex. data=1;2;4;5;3;, it=data[4] -> *it=3
                |1;2;4;5; -> 1;|2;4;5; -> 1;2;|4;5; -> data.begin()+2
        rotate(upper_bound(data.begin(), it, *it), it, it+1) will "rotate" the elements of the given 
            interval [upper_bounds(data.begin(), it, *it), it]
                ex. data=5;3;2;1;6;4;, it=data.begin()
                5;|3;2;1;6;4; -> |5;|3;2;1;6;4; -> 5;|3;2;1;6;4;
                5;3;|2;1;6;4; -> |5;3;|2;1;6;4; -> 3;5;|2;1;6;4;
                3;5;2;|1;6;4; -> |3;5;2;|1;6;4; -> 2;3;5;|1;6;4;
                2;3;5;1;|6;4; -> |2;3;5;1;|6;4; -> 1;2;3;5;|6;4;
                1;2;3;5;6;|4; -> 1;2;3;5;|6;|4; -> 1;2;3;5;6;|4;
                1;2;3;5;6;4;| -> 1;2;3;|5;6;4;| -> 1;2;3;4;5;6;
        */
        rotate(upper_bound(data.begin(), it, *it), it, it+1);
        counter++;
        printKElements(data, counter);
    }
}

// Takes n integers from the user, puts them into a vector and calls insertionSort to sort.
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
    insertionSort(inVector);
    
    return 1;
}