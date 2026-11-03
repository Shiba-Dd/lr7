#include "pch.h"
#include "CppUnitTest.h"
#include "../7.1it/7.1it.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MatrixTests
{
    TEST_CLASS(MatrixTests)
    {
    public:

        int** AllocateMatrix(int rows, int cols) {
            int** a = new int* [rows];
            for (int i = 0; i < rows; i++) {
                a[i] = new int[cols];
            }
            return a;
        }

        void FreeMatrix(int** a, int rows) {
            for (int i = 0; i < rows; i++) {
                delete[] a[i];
            }
            delete[] a;
        }

        TEST_METHOD(TestCalc_Functionality)
        {
            const int r2 = 8, c2 = 1;
            int** m2 = AllocateMatrix(r2, c2);
            for (int i = 0; i < r2; i++) m2[i][0] = 10;
            m2[7][0] = 13;

            int count = 0, sum = 0;
            Calc(m2, r2, c2, count, sum);

            Assert::AreEqual(7, count);
            Assert::AreEqual(70, sum);
            Assert::AreEqual(0, m2[0][0]);
            Assert::AreEqual(13, m2[7][0]);

            FreeMatrix(m2, r2);
        }

        TEST_METHOD(TestSort_SortingLogic)
        {
            const int rows = 4;
            const int cols = 3;
            int** a = AllocateMatrix(rows, cols);

            a[0][0] = 10; a[0][1] = 5;  a[0][2] = 3;
            a[1][0] = 5;  a[1][1] = 8;  a[1][2] = 2;
            a[2][0] = 5;  a[2][1] = 8;  a[2][2] = 9;
            a[3][0] = 5;  a[3][1] = 12; a[3][2] = 1;

            Sort(a, rows, cols);

            Assert::AreEqual(5, a[0][0]); Assert::AreEqual(12, a[0][1]);
            Assert::AreEqual(5, a[1][0]); Assert::AreEqual(8, a[1][1]); Assert::AreEqual(9, a[1][2]);
            Assert::AreEqual(5, a[2][0]); Assert::AreEqual(8, a[2][1]); Assert::AreEqual(2, a[2][2]);
            Assert::AreEqual(10, a[3][0]);

            FreeMatrix(a, rows);
        }
    };
}