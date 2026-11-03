#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;


void Create(int** a, const int rowCount, const int colCount, const int Low, const int High, int i = 0, int j = 0) {
    a[i][j] = Low + rand() % (High - Low + 1);
    if (j < colCount - 1) {
        Create(a, rowCount, colCount, Low, High, i, j + 1);
    }
    else if (i < rowCount - 1) {
        Create(a, rowCount, colCount, Low, High, i + 1, 0);
    }
}


void Print(int** a, const int rowCount, const int colCount, int i = 0, int j = 0) {
    if (j == 0 && i == 0) {
        cout << "---------------------------------------" << endl;
    }
    cout << setw(4) << a[i][j];
    if (j < colCount - 1) {
        Print(a, rowCount, colCount, i, j + 1);
    }
    else {
        cout << endl;
        if (i < rowCount - 1) {
            Print(a, rowCount, colCount, i + 1, 0);
        }
        else {
            cout << "---------------------------------------" << endl;
        }
    }
}
//сума і обнулення
void Calc(int** a, const int rowCount, const int colCount, int& count, int& sum, int i = 0, int j = 0) {
    if (i == 0 && j == 0) {
        count = 0;
        sum = 0;
    }
    //критерій
    if (!(a[i][j] % 2 != 0 && (i + j) % 7 == 0)) {
        sum += a[i][j];
        count++;
        a[i][j] = 0;
    }

    if (j < colCount - 1) {
        Calc(a, rowCount, colCount, count, sum, i, j + 1);
    }
    else if (i < rowCount - 1) {
        Calc(a, rowCount, colCount, count, sum, i + 1, 0);
    }
}

void Change(int** a, const int row1, const int row2, const int colCount, int j = 0) {
    int tmp = a[row1][j];
    a[row1][j] = a[row2][j];
    a[row2][j] = tmp;
    if (j < colCount - 1) {
        Change(a, row1, row2, colCount, j + 1);
    }
}

//головне сортування
void SortSort(int** a, const int rowCount, const int colCount, int i1) {
    if ((a[i1][0] > a[i1 + 1][0]) ||
        (a[i1][0] == a[i1 + 1][0] && a[i1][1] < a[i1 + 1][1]) ||
        (a[i1][0] == a[i1 + 1][0] && a[i1][1] == a[i1 + 1][1] && a[i1][2] < a[i1 + 1][2])) {
        Change(a, i1, i1 + 1, colCount);
    }
    if (i1 < rowCount - 2) {
        SortSort(a, rowCount, colCount, i1 + 1);
    }
}

//зовн функція сортування
void Sort(int** a, const int rowCount, const int colCount, int i0 = 0) {
    SortSort(a, rowCount, colCount, 0);
    if (i0 < rowCount - 2) {
        Sort(a, rowCount, colCount, i0 + 1);
    }
}

int main() {
    srand((unsigned)time(NULL));

    const int rowCount = 7;
    const int colCount = 6;
    const int Low = 9;
    const int High = 61;

    int** S = new int* [rowCount];
    for (int i = 0; i < rowCount; i++) {
        S[i] = new int[colCount];
    }

    Create(S, rowCount, colCount, Low, High);
    cout << "Initial Matrix:" << endl;
    Print(S, rowCount, colCount);

    Sort(S, rowCount, colCount);
    cout << "Sorted Matrix:" << endl;
    Print(S, rowCount, colCount);

    int count = 0;
    int sum = 0;
    Calc(S, rowCount, colCount, count, sum);

    cout << "Count = " << count << endl;
    cout << "Sum   = " << sum << endl;

    cout << "Modified Matrix (with zeros):" << endl;
    Print(S, rowCount, colCount);

    for (int i = 0; i < rowCount; i++) {
        delete[] S[i];
    }
    delete[] S;

    return 0;
}