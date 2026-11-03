#include "pch.h"
#include "CppUnitTest.h"
#include "../7.1rek/7.1rek.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest71rek
{
    TEST_CLASS(MatrixFunctionTests)
    {
    private:
        // Допоміжна функція для виділення пам'яті під матрицю
        int** CreateMatrix(int rows, int cols) {
            int** matrix = new int* [rows];
            for (int i = 0; i < rows; i++) {
                matrix[i] = new int[cols];
            }
            return matrix;
        }

        // Допоміжна функція для звільнення пам'яті
        void FreeMatrix(int** matrix, int rows) {
            for (int i = 0; i < rows; i++) {
                delete[] matrix[i];
            }
            delete[] matrix;
        }

    public:

        // 1. Тест рекурсивного генератора матриці Create
        TEST_METHOD(TestCreateFunction)
        {
            const int rows = 3;
            const int cols = 3;
            const int low = 9;
            const int high = 61;

            int** a = CreateMatrix(rows, cols);
            Create(a, rows, cols, low, high);

            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    Assert::IsTrue(a[i][j] >= low && a[i][j] <= high, L"Елемент виходить за межі заданого діапазону");
                }
            }

            FreeMatrix(a, rows);
        }

        // 2. Тест перестановки рядків Change
        TEST_METHOD(TestChangeRowsFunction)
        {
            const int rows = 2;
            const int cols = 3;
            int** a = CreateMatrix(rows, cols);

            a[0][0] = 1; a[0][1] = 2; a[0][2] = 3;
            a[1][0] = 4; a[1][1] = 5; a[1][2] = 6;

            Change(a, 0, 1, cols);

            Assert::AreEqual(4, a[0][0]);
            Assert::AreEqual(5, a[0][1]);
            Assert::AreEqual(6, a[0][2]);
            Assert::AreEqual(1, a[1][0]);
            Assert::AreEqual(2, a[1][1]);
            Assert::AreEqual(3, a[1][2]);

            FreeMatrix(a, rows);
        }

        // 3. Тест підрахунку, суми та обнулення Calc
        TEST_METHOD(TestCalcFunction)
        {
            const int rows = 2;
            const int cols = 3;
            int** a = CreateMatrix(rows, cols);

            // a[0][0]=9  (непарне, i+j=0 % 7 == 0) -> НЕ відповідає критерію (виключається)
            // a[0][1]=10 (парне)                   -> відповідає критерію
            // a[0][2]=11 (непарне, i+j=2 % 7 != 0) -> відповідає критерію
            // a[1][0]=12 (парне)                   -> відповідає критерію
            // a[1][1]=13 (непарне, i+j=2 % 7 != 0) -> відповідає критерію
            // a[1][2]=14 (парне)                   -> відповідає критерію
            a[0][0] = 9;  a[0][1] = 10; a[0][2] = 11;
            a[1][0] = 12; a[1][1] = 13; a[1][2] = 14;

            int count = 0;
            int sum = 0;

            Calc(a, rows, cols, count, sum);

            // Очікувані значення: 5 елементів підходять, сума = 10 + 11 + 12 + 13 + 14 = 60
            Assert::AreEqual(5, count);
            Assert::AreEqual(60, sum);

            // a[0][0] було проігноровано, тому воно НЕ обнуляється
            Assert::AreEqual(9, a[0][0]);

            // a[1][2] підпало під критерій, тому воно обнуляється
            Assert::AreEqual(0, a[1][2]);

            FreeMatrix(a, rows);
        }
        // 4. Тест сортування за 3 ключами Sort
        TEST_METHOD(TestSortFunction)
        {
            const int rows = 3;
            const int cols = 3;
            int** a = CreateMatrix(rows, cols);

            // Рядок 0: [20, 50, 10]
            // Рядок 1: [10, 40, 30] -> має стати першим (за зростанням col 0)
            // Рядок 2: [10, 40, 50] -> однакові col 0 та col 1, має сортувати за спаданням col 2
            a[0][0] = 20; a[0][1] = 50; a[0][2] = 10;
            a[1][0] = 10; a[1][1] = 40; a[1][2] = 30;
            a[2][0] = 10; a[2][1] = 40; a[2][2] = 50;

            Sort(a, rows, cols);

            // Очікуваний порядок рядків: [10, 40, 50], [10, 40, 30], [20, 50, 10]
            Assert::AreEqual(10, a[0][0]);
            Assert::AreEqual(50, a[0][2]); // 50 > 30 при однакових перших двох елементах

            Assert::AreEqual(10, a[1][0]);
            Assert::AreEqual(30, a[1][2]);

            Assert::AreEqual(20, a[2][0]);

            FreeMatrix(a, rows);
        }
    };
}
