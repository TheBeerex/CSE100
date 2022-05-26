/*
    book psuedocode from pages 71/72 

    FIND-MAX-CROSSING-SUBARRAY (A, low, mid, high)
        left-sum = -INFINITY
        sum = 0
        for i = mid downto low
            sum = sum + A[i]
            if sum > left-sum
                left-sum = sum
                max-left = i
        right-sum = -INFINITY
        sum = 0
        for j = mid + 1 to high
            sum = sum + A[j]
            if sum > right-sum
                right-sum = sum
                max-right = j
        return (max-left, max-right, left-sum + right-sum)


    FIND-MAXIMUM-SUBARRAY (A, low, high) 
        if high == low
            return (low, high, A[low]) // base case: only one element
        else 
            mid = [ (low + high) / 2 ]
            (left-low, left-high, left-sum) = FIND-MAXIMUM-SUBARRAY (A, low, mid)
            (right-low, right-high, right-sum) = FIND-MAXIMUM-SUBARRAY(A, mid+1, high)
            (cross-low, cross-high, cross-sum) = FIND-MAX-CROSSING-SUBARRAY(A, low, mid, high)
            if left-sum >= right-sum and left-sum >= cross-sum
                return (left-low, left-high, left-sum)
            elseif right-sum >= left-sum and right-sum >= cross-sum
                return (right-low, right-high, right-sum)
            else 
                return (cross-low, cross-high, cross-sum)

*/


// Author: TheBeerex
// Lab_03 ~~ lab3.cpp

#include <vector>
#include <iostream>
#include <climits>

using namespace std;

// Utility to print entire vector
void printVector(vector<int> &vect) {
    for (auto it = vect.begin(); it != vect.end(); it++) {
        cout << *it << ";";
    }
}

// A utility function to find maximum of two integers
int max(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}

// A utility function to find maximum of three integers
int max(int a, int b, int c) {
    return max(max(a, b), c);
}



// Finds and returns the sum of the maximum subarray which includes data[mid]
int findMaxCrossingSubarraySum (vector<int> data, int low, int mid, int high) {

    // Elements left of mid
    int sum = 0;
    int leftSum = INT_MIN;
    for (int i = mid; i >= low; i--) {
        sum = sum + data[i];
        if (sum > leftSum)
            leftSum = sum;
    }

    // Elements right of mid
    sum = 0;
    int rightSum = INT_MIN;
    for (int i = mid+1; i <= high; i++) {
        sum = sum + data[i];
        if (sum > rightSum)
            rightSum = sum;
    }

    // Return sum of elements on left and right of mid
    return (leftSum + rightSum);
    // return max(leftSum + rightSum, leftSum, rightSum);
}

// Finds and returns the sum of the maximum subarray of data over the interval [low:high]
int findMaxSubarraySum (vector<int> data, int low, int high) {
    //Base case: only one element
    if (low == high)
        return data[low];

    //Get midpoint of [low:high]
    int mid = (low+high)/2;

    //Get Left Max Sum
    int leftMax = findMaxSubarraySum(data, low, mid);

    //Get Right Max Sum
    int rightMax = findMaxSubarraySum(data, mid+1, high);

    //Get Crossing Max Sum
    int crossMax = findMaxCrossingSubarraySum(data, low, mid, high);

    //Return max of found sums
    return( max(leftMax, rightMax, crossMax) );

}



// Takes n integers from the user, puts them into a vector and calls findMaxSum. Prints resulting output.
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
    int theMax = findMaxSubarraySum(inVector, 0, n-1);

    cout << theMax;
}