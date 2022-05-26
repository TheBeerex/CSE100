// Author: TheBeerex
// Lab_08 ~~ Matrix Chain Multiplication

#include <iostream>
#include <climits>

using namespace std;

void printOptimalParens(int** s, int i, int j) {
    if (i==j) {
        cout << "A" << i-1;
    } else {
        cout << "(";
        printOptimalParens(s, i, s[i][j]);
        printOptimalParens(s, s[i][j]+1, j);
        cout << ")";
    }
    
}

void matrixChainOrder(int p[], int size) {
    int n = size;

    int** m = new int*[n];
    int** s = new int*[n];

    int i, j, k, L, q;

    for (i = 0; i < n; i++) {
        m[i] = new int[n];
        s[i] = new int[n];
        for (j = 0; j < n; j++) {
            m[i][j] = 0;
            s[i][j] = 0;
        }
    }
    
    for (L = 2; L < n; L++) {
        for (i = 1; i < n-L+1; i++) {
            j = i + L - 1;
            m[i][j] = INT_MAX;
            for (k = i; k <= j-1; k++){
                q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    cout << m[1][n-1] << endl;

    printOptimalParens(s, 1, n-1);
    
    cout << endl;

    delete m;
    delete s;
}

int main() {
    int size;

    cin >> size;
    size++;

    int* arr = new int[size];

    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }
    
    matrixChainOrder(arr, size);

    delete arr;

    return 0;
}
