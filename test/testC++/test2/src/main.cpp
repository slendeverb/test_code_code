#include <iostream>
#include <vector>
using namespace std;

using Matrix = std::vector<std::vector<int>>;

std::istream& operator>>(std::istream& in, Matrix& matrix) {
    size_t n = matrix.size();
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            std::cin >> matrix[i][j];
        }
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Matrix& matrix) {
    size_t n = matrix.size();
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
    return out;
}

Matrix operator+(const Matrix& a, const Matrix& b) {
    int n = a.size();
    Matrix res(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[i][j] = a[i][j] + b[i][j];
        }
    }
    return res;
}

Matrix operator-(const Matrix& a, const Matrix& b) {
    int n = a.size();
    Matrix res(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[i][j] = a[i][j] - b[i][j];
        }
    }
    return res;
}

Matrix operator*(const Matrix& a, const Matrix& b) {
    int n = a.size();
    Matrix res(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                res[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return res;
}

void initSubMatrix(int RStart,
                   int CStart,
                   int n,
                   Matrix& dst,
                   const Matrix& src) {
    dst.resize(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dst[i][j] = src[RStart + i][CStart + j];
        }
    }
}

Matrix concateMatrix(const Matrix& c11,
                     const Matrix& c12,
                     const Matrix& c21,
                     const Matrix& c22) {
    int n = c11.size();
    Matrix res(2 * n, std::vector<int>(2 * n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[i][j] = c11[i][j];
            res[i][j + n] = c12[i][j];
            res[i + n][j] = c21[i][j];
            res[i + n][j + n] = c22[i][j];
        }
    }
    return res;
}

Matrix strassen(const Matrix& a, const Matrix& b) {
    int n = a.size();
    if (n == 2) {
        return a * b;
    }
    Matrix a11, a12, a21, a22;
    Matrix b11, b12, b21, b22;

    initSubMatrix(0, 0, n / 2, a11, a);
    initSubMatrix(0, n / 2, n / 2, a12, a);
    initSubMatrix(n / 2, 0, n / 2, a21, a);
    initSubMatrix(n / 2, n / 2, n / 2, a22, a);

    initSubMatrix(0, 0, n / 2, b11, b);
    initSubMatrix(0, n / 2, n / 2, b12, b);
    initSubMatrix(n / 2, 0, n / 2, b21, b);
    initSubMatrix(n / 2, n / 2, n / 2, b22, b);

    Matrix m1{strassen(a11, b12 - b22)};
    Matrix m2{strassen(a11 + a12, b22)};
    Matrix m3{strassen(a21 + a22, b11)};
    Matrix m4{strassen(a22, b21 - b11)};
    Matrix m5{strassen(a11 + a22, b11 + b22)};
    Matrix m6{strassen(a12 - a22, b21 + b22)};
    Matrix m7{strassen(a11 - a21, b11 + b12)};

    Matrix c11{m5 + m4 - m2 + m6};
    Matrix c12{m1 + m2};
    Matrix c21{m3 + m4};
    Matrix c22{m5 + m1 - m3 - m7};

    return concateMatrix(c11, c12, c21, c22);
}

void solve() {
    int n = 0;
    std::cin >> n;
    Matrix matrixA(n, std::vector<int>(n, 0));
    Matrix matrixB(n, std::vector<int>(n, 0));

    std::cin >> matrixA >> matrixB;
    Matrix matrixC{strassen(matrixA, matrixB)};
    std::cout << matrixC;
}

int main() {
    solve();
    return 0;
}