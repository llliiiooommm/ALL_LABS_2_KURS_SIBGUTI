#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Выводим массив
void print(int* arr){
    if (arr == nullptr) return;

    int size = arr[0];

    cout << size << ": ";

    for (int i = 1; i <= size; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}
// Вызываем внутри функцию вывода каждой строки
void printMatrix(int** matrix, int rows){
    for (int i = 0; i < rows; i++){
        print(matrix[i]);
    }
}

// Создаются рандомные элементы массива
int* genRandArray(int size, int maxValue){
    if (size == 0) return nullptr;
    
    int *arr = new int[size + 1];

    arr[0] = size;

    for (int i = 1; i <= size; i++){
        arr[i] = rand() % maxValue;
    }

    return arr;
}

// Вызываю для каждой строки заполнение рандомными элементами
int** genRandMatrix(int size, int maxValue){
    if (size == 0) return nullptr;

    int** matrix = new int*[size];

    for (int i = 0; i < size; i++){
        int rowSize = rand() % 10;
        matrix[i] = genRandArray(rowSize, maxValue);
    }

    return matrix;
}


int main(){
    srand(time(0));

    int size = rand() % 10;
    int maxValue = 100;
    int** matrix = genRandMatrix(size, maxValue);

    cout << size << endl;
    printMatrix(matrix, size);

    // очистка памяти
    for (int i = 0; i < size; i++){
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}
