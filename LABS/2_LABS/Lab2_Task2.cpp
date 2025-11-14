#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(time(0));

    int rows;
    cout << "Введите количество строк: ";
    cin >> rows;

    // Создаем вектор векторов — каждая строка может иметь разную длину
    vector<vector<int>> matrix;

    // Заполняем каждую строку случайным количеством элементов
    for (int i = 0; i < rows; i++) {
        int cols = rand() % 5 + 1; // от 1 до 5 элементов в строке
        vector<int> row;
        for (int j = 0; j < cols; j++) {
            row.push_back(rand() % 100); // случайные числа 0-99
        }
        matrix.push_back(row);
    }

    // Выводим построчно
    cout << "\nМатрица с разным количеством элементов в строках:\n";
    for (int i = 0; i < rows; i++) {
        cout << "Строка " << i + 1 << ": ";
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}