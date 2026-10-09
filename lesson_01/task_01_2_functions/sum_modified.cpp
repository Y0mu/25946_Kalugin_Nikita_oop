#include "sum_modified.h"

#include <iostream>
#include <random>

// Чтобы не писать std:: перед каждым именем из стандартной библиотеки.
using namespace std;

// Реализация "модифицированной" функции.
int ModifiedSum(int x, int y) {
    // Генератор случайных чисел из стандартной библиотеки <random>.
    // Делаем его static, чтобы состояние сохранялось между вызовами функции
    // (иначе при каждом вызове последовательность случайных чисел начиналась бы заново).
    static mt19937 generator{ random_device{}() };

    // Добавка — случайное число от 0 до 99.
    uniform_int_distribution<int> addition{ 0, 99 };

    // Монетка: 0 или 1, обе стороны равновероятны.
    uniform_int_distribution<int> coin{ 0, 1 };

    int result = x + y;

    // В половине случаев добавляем случайное число.
    if (coin(generator) == 1) {
        int extra = addition(generator);
        cout << "  extra = " << extra << '\n';
        result = result + extra;
    } else {
        cout << "  extra = 0\n";
    }

    return result;
}
