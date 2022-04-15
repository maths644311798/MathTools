#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

class Matrix
{
public:
    //m*n matrix
    int m, n;
    vector<vector<double>> data;
    Matrix(int out_m = 1, int out_n = 1) : m(out_m), n(out_n)
    {
        vector<double> temp(n, 0);
        for (int i = 0; i < m; ++i) data.push_back(temp);
    }
    Matrix(const Matrix& second_matrix)
    {
        m = second_matrix.m;
        n = second_matrix.n;
        for (int i = 0; i < m; ++i)
        {
            vector<double> temp;
            for (int j = 0; j < n; ++j)
                temp.push_back(second_matrix.data[i][j]);
            data.push_back(temp);
        }
    }

    Matrix& operator=(const Matrix& second_matrix)
    {
        m = second_matrix.m;
        n = second_matrix.n;
        for (int i = 0; i < m; ++i)
        {
            vector<double> temp;
            for (int j = 0; j < n; ++j)
                temp.push_back(second_matrix.data[i][j]);
            data.push_back(temp);
        }
        return *this;
    }
};

Matrix& operator+(const Matrix& A,const Matrix& B)
{
    Matrix res(A);
    if (A.m == B.m && A.n == B.n)
    {
        for (int i = 0; i < A.m; ++i)
        {
            for (int j = 0; j < A.n; ++j)
                res.data[i][j] += B.data[i][j];
        }
    }
    else
    {
        cerr << "Matrix parameters do not match\n";
    }
    return res;
}

Matrix& operator*(const Matrix& A, const Matrix& B)
{
    Matrix res(A.m, B.n);
    if (A.n == B.m)
    {
        for (int i = 0; i < res.m; ++i)
        {
            for (int j = 0; j < res.n; ++j)
            {
                res.data[i][j] = 0;
                for (int k = 0; k < A.n; ++k)
                    res.data[i][j] += A.data[i][k] * B.data[k][j];
            }
        }
    }
    else
    {
        cerr << "Matrix parameters do not match\n";
    }
    return res;
}
