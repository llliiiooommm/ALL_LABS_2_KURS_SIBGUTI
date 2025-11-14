#include <iostream>

template <typename T>
class Matrix {
private:
    T** M;
    int m, n;

public:
    Matrix() {
        M = nullptr;
        m = 0;
        n = 0;
    }

    Matrix(int rows, int cols) {
        m = rows;
        n = cols;
        M = new T*[m];
        for (int i = 0; i < m; i++) {
            M[i] = new T[n]();
        }
    }

    Matrix(Matrix &copy) {
        m = copy.m;
        n = copy.n;
        M = new T*[m];
        for (int i = 0; i < m; i++) {
            M[i] = new T[n];
            for (int j = 0; j < n; j++) {
                M[i][j] = copy.M[i][j];
            }
        }
    }

    Matrix& operator=(Matrix &copy) {
        if (this == &copy) {
            return *this;
        }

        for (int i = 0; i < m; i++) {
            delete[] M[i];
        }
        delete[] M;

        m = copy.m;
        n = copy.n;
        M = new T*[m];
        for (int i = 0; i < m; i++) {
            M[i] = new T[n];
            for (int j = 0; j < n; j++) {
                M[i][j] = copy.M[i][j];
            }
        }

        return *this;
    }

    ~Matrix() {
        for (int i = 0; i < m; i++) {
            delete[] M[i];
        }
        delete[] M;
    }

    T GetM(int i, int j) {
        return M[i][j];
    }

    void SetM(int i, int j, T value) {
        M[i][j] = value;
    }

    void Print(const char* name) {
        std::cout << "Object: " << name << std::endl;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                std::cout << M[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "---------------------" << std::endl;
    }
};

// ============ ВАРИАНТ 1: int ============
int main() {
    Matrix<int> M(3, 4);
    M.Print("M");

    int i, j;
    for (i = 0; i < 2; i++)
        for (j = 0; j < 3; j++)
            M.SetM(i, j, i + j);

    M.Print("M");

    Matrix<int> M1 = M;
    M1.Print("M1");

    Matrix<int> M2;
    M2 = M;
    M2.Print("M2");

    Matrix<int> M3;
    M3 = M2 = M1 = M;
    M3.Print("M3");

    return 0;
}
/*
// ============ ВАРИАНТ 2: double ============
int main() {
    Matrix<double> M(3, 4);
    M.Print("M");

    int i, j;
    for (i = 0; i < 2; i++)
        for (j = 0; j < 3; j++)
            M.SetM(i, j, (i + j) * 0.5);

    M.Print("M");

    Matrix<double> M1 = M;
    M1.Print("M1");

    Matrix<double> M2;
    M2 = M;
    M2.Print("M2");

    Matrix<double> M3;
    M3 = M2 = M1 = M;
    M3.Print("M3");

    return 0;
}
*/