#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(time(0)); // для случайных чисел

    int N;
    cout << "Введите размер матрицы N: ";
    cin >> N;

    // Создаем динамический двумерный массив N x N
    vector<vector<int>> matrix(N, vector<int>(N));

    // Заполняем случайными числами от -50 до 50
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = rand() % 101 - 50; // [-50, 50]
        }
    }

    // Выводим матрицу
    cout << "\nИсходная матрица:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }

    // Создаем одномерный массив D (размер N*N)
    vector<int> D(N * N);

    // a) По правым диагоналям, начиная с правого верхнего элемента
    cout << "\n\na) По правым диагоналям (с правого верхнего):\n";
    int idx = 0;
    // Правые диагонали: сумма индексов j - i = const, идем от правого верхнего угла
    for (int d = N - 1; d >= -(N - 1); d--) { // d = j - i
        for (int i = 0; i < N; i++) {
            int j = i + d;
            if (j >= 0 && j < N) {
                D[idx++] = matrix[i][j];
                cout << matrix[i][j] << " ";
            }
        }
    }
    cout << endl;

    // b) По левым диагоналям, начиная с левого верхнего элемента
    cout << "\nb) По левым диагоналям (с левого верхнего):\n";
    idx = 0;
    // Левые диагонали: сумма индексов i + j = const
    for (int s = 0; s <= 2 * (N - 1); s++) {
        for (int i = 0; i < N; i++) {
            int j = s - i;
            if (j >= 0 && j < N) {
                D[idx++] = matrix[i][j];
                cout << matrix[i][j] << " ";
            }
        }
    }
    cout << endl;

    // c) По спирали, начиная с центрального элемента
    cout << "\nc) По спирали из центра:\n";
    idx = 0;
    int centerX = N / 2;
    int centerY = N / 2;
    D[idx++] = matrix[centerX][centerY]; // центр

    // Спираль: шаги 1,1,2,2,3,3,... в направлениях: вправо, вниз, влево, вверх
    int dx[] = {0, 1, 0, -1}; // направления: вправо, вниз, влево, вверх
    int dy[] = {1, 0, -1, 0};
    int steps = 1;
    int x = centerX, y = centerY;

    while (idx < N * N) {
        for (int dir = 0; dir < 4; dir++) { // 4 направления
            for (int step = 0; step < steps && idx < N * N; step++) {
                x += dx[dir];
                y += dy[dir];
                if (x >= 0 && x < N && y >= 0 && y < N) {
                    D[idx++] = matrix[x][y];
                    cout << matrix[x][y] << " ";
                }
            }
            if (dir % 2 == 1) steps++; // увеличиваем шаг после каждого второго направления
        }
    }
    cout << endl;

    // d) По спирали, начиная с левого верхнего элемента
    cout << "\nd) По спирали из левого верхнего угла:\n";
    idx = 0;
    int top = 0, bottom = N - 1, left = 0, right = N - 1;
    while (top <= bottom && left <= right) {
        // Вправо
        for (int j = left; j <= right && idx < N * N; j++) {
            D[idx++] = matrix[top][j];
            cout << matrix[top][j] << " ";
        }
        top++;
        // Вниз
        for (int i = top; i <= bottom && idx < N * N; i++) {
            D[idx++] = matrix[i][right];
            cout << matrix[i][right] << " ";
        }
        right--;
        // Влево
        for (int j = right; j >= left && idx < N * N; j--) {
            D[idx++] = matrix[bottom][j];
            cout << matrix[bottom][j] << " ";
        }
        bottom--;
        // Вверх
        for (int i = bottom; i >= top && idx < N * N; i--) {
            D[idx++] = matrix[i][left];
            cout << matrix[i][left] << " ";
        }
        left++;
    }
    cout << endl;

    return 0;
}