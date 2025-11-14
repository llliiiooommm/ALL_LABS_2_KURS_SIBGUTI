#include <iostream>
#include <cstdlib>
#include <ctime>

class Matrix {
private:
    int** mat;      // двумерный массив
    int rows, cols; // размеры
    long sum;       // сумма элементов

public:
    // a. Конструктор по умолчанию — пустая матрица
    Matrix() {
        rows = cols = 0;
        mat = nullptr;
        sum = 0;
    }

    // b. Единичная квадратная матрица размера n
    Matrix(int n) {
        rows = cols = n;
        mat = new int*[n];
        for (int i = 0; i < n; i++) {
            mat[i] = new int[n];
            for (int j = 0; j < n; j++) {
                mat[i][j] = (i == j) ? 1 : 0;
            }
        }
        sum = 0;
    }

    // c. Матрица заданного размера (заполняется нулями)
    Matrix(int r, int c) {
        rows = r;
        cols = c;
        mat = new int*[r];
        for (int i = 0; i < r; i++) {
            mat[i] = new int[c];
            for (int j = 0; j < c; j++) {
                mat[i][j] = 0;
            }
        }
        sum = 0;
    }

    // Деструктор — освобождаем память
    ~Matrix() {
        if (mat != nullptr) {
            for (int i = 0; i < rows; i++) {
                delete[] mat[i];
            }
            delete[] mat;
        }
    }

    // Ввод с клавиатуры
    void input() {
        std::cout << "Введите элементы матрицы " << rows << "x" << cols << ":\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cin >> mat[i][j];
            }
        }
    }

    // Заполнение случайными числами (от 0 до 99)
    void fillRandom() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                mat[i][j] = rand() % 100;
            }
        }
    }

    // Вывод матрицы
    void print() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << mat[i][j] << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    // Подсчёт суммы элементов
    void calcSum() {
        sum = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                sum += mat[i][j];
            }
        }
    }

    // Получить сумму
    long getSum() {
        return sum;
    }

    // Заполнить по правилу: элемент = (номер строки) * (номер столбца)
    // Нумерация с 1!
    void fillByProduct() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                mat[i][j] = (i + 1) * (j + 1);
            }
        }
    }
    void resize(int newRows, int newCols){
        int** buff=new int*[newRows];
        for(int i=0; i<newRows; i++){
            buff[i]=new int[newCols];
            for(int j=0; j<newCols; j++){
                if(i>=rows){
                    buff[i][j]=rand()%100+1;
                }
                else if(j>=cols){
                    buff[i][j]=rand()%100+1;
                }
                else{
                    buff[i][j]=mat[i][j];
                }
            }
        }
        if (mat != nullptr) {
            for (int i = 0; i < rows; i++) {
                delete[] mat[i];
            }
            delete[] mat;
        }
        mat=buff;
        rows=newRows;
        cols=newCols;
        sum=0;
    }
};

// Основная программа
int main() {
    srand(time(0));

    // Создаём 4 матрицы разными конструкторами
    Matrix M1;           // a. по умолчанию
    Matrix M2(3);        // b. единичная 3x3
    Matrix M3(3, 4);     // c. 3x4
    Matrix M4(2, 3);     // c. 2x3

    // Выводим M2, M3, M4
    std::cout << "M2 (единичная):\n";
    M2.print();

    std::cout << "M3 (3x4, нули):\n";
    M3.print();

    std::cout << "M4 (2x3, нули):\n";
    M4.print();

    // Заполняем M2 по правилу i*j
    M2.fillByProduct();
    std::cout << "M2 после заполнения (i+1)*(j+1):\n";
    M2.print();

    // Заполняем M3 случайными числами
    M3.fillRandom();
    std::cout << "M3 после случайного заполнения:\n";
    M3.print();

    // Вводим M4 с клавиатуры
    M4.input();
    std::cout << "M4 после ввода:\n";
    M4.print();

    // Считаем сумму для M3
    M3.calcSum();
    std::cout << "Сумма элементов M3: " << M3.getSum() << "\n";

    M4.resize(3, 3);
    std::cout << "M4 после изменения размера:\n";
    M4.print();
    return 0;
};