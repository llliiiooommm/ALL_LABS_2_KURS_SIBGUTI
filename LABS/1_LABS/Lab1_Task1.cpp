#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


void print(int* arr){
    int size = arr[0];

    cout << size << ": ";

    for (int i = 1; i <= size; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}



int* genRandArray(int size, int maxValue){
    if (size == 0) return nullptr;
    
    int *arr = new int[size + 1];

    arr[0] = size;

    for (int i = 1; i <= size; i++){
        arr[i] = rand() % maxValue;
    }

    return arr;
}

int main(){
    srand(time(0));

    int size = rand() % 10;
    int maxValue = 100;
    int* arr = genRandArray(size, maxValue);

    print(arr);

    delete[] arr;
    return 0;
}
