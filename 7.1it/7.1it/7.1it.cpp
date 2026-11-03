#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

//створення та заповнення матриці
void Create(int** a, const int rowCount, const int colCount, const int Low, const int High) {
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {
            a[i][j] = Low + rand() % (High - Low + 1);
        }
    }
}

//форматне виведення
void Print(int** a, const int rowCount, const int colCount) {
    cout << "---------------------------------------" << endl;
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {
            cout << setw(4) << a[i][j];
        }
        cout << endl;
    }
    cout << "---------------------------------------" << endl;
}

//сума і к-сть всіх за критерієм 
void Calc(int** a, const int rowCount, const int colCount, int& count, int& sum) {
    count = 0;
    sum = 0;
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {
            // КРИТЕРІЙ: всі крім непарних з сумою індексів кратною 7
            if (!(a[i][j] % 2 != 0 && (i + j) % 7 == 0)) {
                sum += a[i][j];
                count++;
                a[i][j] = 0;
            }
        }
    }
}

//допоміжна функція міняння місцями двох рядків
void Change(int** a, const int row1, const int row2, const int colCount) {
    for (int j = 0; j < colCount; j++) {
        int tmp = a[row1][j];
        a[row1][j] = a[row2][j];
        a[row2][j] = tmp;
    }
}

// Впорядкування рядків за ключами: 0-й стовпчик (зростання), 1-й (спадання), 2-й (спадання)
void Sort(int** a, const int rowCount, const int colCount) {
    for (int i0 = 0; i0 < rowCount - 1; i0++) {
        for (int i1 = 0; i1 < rowCount - i0 - 1; i1++) {
            if ((a[i1][0] > a[i1 + 1][0]) ||
                (a[i1][0] == a[i1 + 1][0] && a[i1][1] < a[i1 + 1][1]) ||
                (a[i1][0] == a[i1 + 1][0] && a[i1][1] == a[i1 + 1][1] && a[i1][2] < a[i1 + 1][2])) {
                Change(a, i1, i1 + 1, colCount);
            }
        }
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

    // Звільнення пам'яті
    for (int i = 0; i < rowCount; i++) {
        delete[] S[i];
    }
    delete[] S;

    return 0;
}