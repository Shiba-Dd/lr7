#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;


void Create(int** a, const int n, const int Low, const int High, int i = 0, int j = 0) {
    a[i][j] = Low + rand() % (High - Low + 1);
    if (j < n - 1) {
        Create(a, n, Low, High, i, j + 1);
    }
    else if (i < n - 1) {
        Create(a, n, Low, High, i + 1, 0);
    }
}

void Print(int** a, const int n, int i = 0, int j = 0) {
    if (i == 0 && j == 0) {
        cout << "---------------------------------------" << endl;
    }
    cout << setw(5) << a[i][j];
    if (j < n - 1) {
        Print(a, n, i, j + 1);
    }
    else {
        cout << endl;
        if (i < n - 1) {
            Print(a, n, i + 1, 0);
        }
        else {
            cout << "---------------------------------------" << endl;
        }
    }
}


int MaxMainDiagonal(int** a, const int n, int i = 1, int max = 0) {
    if (i == 1) {
        max = a[0][0]; 
    }
    if (i < n) {
        if (a[i][i] > max) {
            max = a[i][i];
        }
        return MaxMainDiagonal(a, n, i + 1, max);
    }
    return max;
}

int main() {
    srand((unsigned)time(NULL));

    const int n = 5;
    const int Low = -10;
    const int High = 50;

    int** a = new int* [n];
    for (int i = 0; i < n; i++) {
        a[i] = new int[n];
    }

    Create(a, n, Low, High);
    cout << "Matrix:" << endl;
    Print(a, n);

    int maxDiag = MaxMainDiagonal(a, n);
    cout << "Max element on main diagonal = " << maxDiag << endl;

    for (int i = 0; i < n; i++) {
        delete[] a[i];
    }
    delete[] a;

    return 0;
}