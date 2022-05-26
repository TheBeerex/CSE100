// Author: TheBeerex
// Lab_07 ~ Rod Cutting Problem

#include <iostream>
#include <cmath>
#include <vector>
#include <climits>

using namespace std;

// Based on psuedocode from page 369 of textbook

int* cut_rod (int price[], int n) {
    int* r = new int[n+1]; // Max revenue
    int* s = new int[n+1]; // Rod Sizes
    r[0] = 0;

    int i, j;
    for (j = 1; j <= n; j++) {
        int max = INT_MIN;
        for (i = 1; i <= j; i++) {
            if ( max < (price[i] + r[j-i]) ) {
                max = price[i] + r[j-i];
                s[j] = i;
            }
        }
        r[j] = max;
    }
    delete[] r;

    return s;
}

void print_cut_rod_solution (int price[], int n) {
    int* s = cut_rod (price, n);

    int sum = 0;
    vector<int> sol;

    // find sum and its components
    int i = n;
    while (i > 0) {
        sol.push_back(s[i]);
        sum += price[s[i]];
        i = i - s[i];
    }
    
    // Print sum and its components
    cout << sum << endl;
    for (auto it = sol.begin(); it != sol.end(); it++) {
        cout << *it << " ";
    }
    cout << -1 << endl;

    delete[] s;

    return;
}


int main() {
    int* prices;
    int n;

    cin >> n;

    if (n > 0) {
        
        prices = new int[n+1];
		
        prices[0] = 0;

		for (int i = 1; i < n+1; i++) {
			cin >> prices[i];
		}

        print_cut_rod_solution(prices, n);

        delete[] prices;
    }

    return 1;
}