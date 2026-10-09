#include "sum_required.h"

#include <iostream>

// Чтобы не писать std:: перед каждым именем из стандартной библиотеки.
using namespace std;

// Реализация "требуемой" функции.
// Здесь всё максимально просто: сложили и вернули результат.
int Sum(int x, int y) {
    int result = x + y;
    return result;
}

// Небольшая вспомогательная функция для красивого вывода.
void PrintTitle(const char* title) {
    cout << "--- " << title << " ---\n";
}
