#include "sum_required.h"

#include <iostream>
#include <random>

// Чтобы не писать std:: перед каждым именем из стандартной библиотеки.
using namespace std;

namespace modified {

// Задание 02.II. "Модифицированная" функция.
// Сигнатура полностью совпадает с required::Sum(int&, int&),
// отличие только в поведении: добавляем случайную добавку с вероятностью 50%.
int Sum(int& x, int& y) {
    // Генератор делаем static, чтобы состояние не сбрасывалось между вызовами.
    static mt19937 generator{ random_device{}() };

    // Монетка: 0 или 1 с одинаковой вероятностью.
    uniform_int_distribution<int> coin{ 0, 1 };

    // Случайная добавка от 0 до 99.
    uniform_int_distribution<int> addition{ 0, 99 };

    // Аргументы меняем так же, как и в требуемой функции.
    x = x + 1;
    y = y + 1;

    int result = x + y;

    // В половине случаев прибавляем случайное число.
    if (coin(generator) == 1) {
        int extra = addition(generator);
        cout << "  extra = " << extra << '\n';
        result = result + extra;
    } else {
        cout << "  extra = 0\n";
    }

    return result;
}

}  // namespace modified
