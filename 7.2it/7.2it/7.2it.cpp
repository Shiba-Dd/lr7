#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;


void Create(int** a, const int n, const int Low, const int High) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = Low + rand() % (High - Low + 1);
        }
    }
}


void Print(int** a, const int n) {
    cout << "---------------------------------------" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(5) << a[i][j];
        }
        cout << endl;
    }
    cout << "---------------------------------------" << endl;
}

int MaxMainDiagonal(int** a, const int n) {
    int max = a[0][0];
    for (int i = 1; i < n; i++) {
        if (a[i][i] > max) {
            max = a[i][i];
        }
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