#pragma once

// Задания 02.III и 02.IV. Шаблоны функций.
//
// 02.III — функция должна работать не только с int, но и с double.
// 02.IV  — "требуемая" и "модифицированная" функции, переписанные через шаблоны.
//
// Шаблон — это заготовка функции. Компилятор сам создаёт нужный вариант
// (для int, для double, ...) в момент компиляции, поэтому шаблоны
// обычно пишут прямо в заголовочном файле.

#include <iostream>
#include <random>

// Чтобы не писать std:: перед каждым именем из стандартной библиотеки.
using namespace std;

namespace required {

// Требуемая функция в виде шаблона: тип T подставляется компилятором.
// Параметры принимаем по константной ссылке — копий нет, менять нельзя.
template <typename T>
T Sum(const T& x, const T& y) {
    return x + y;
}

}  // namespace required

namespace modified {

// Модифицированная функция в виде шаблона.
// Работает как required::Sum, но в половине случаев прибавляет случайную добавку.
template <typename T>
T Sum(const T& x, const T& y) {
    // static внутри шаблонной функции: у каждого варианта (для int, для double)
    // будет свой собственный генератор.
    static mt19937 generator{ random_device{}() };

    uniform_int_distribution<int> coin{ 0, 1 };
    uniform_int_distribution<int> addition{ 0, 99 };

    T result = x + y;

    if (coin(generator) == 1) {
        T extra = static_cast<T>(addition(generator));
        cout << "  extra = " << extra << '\n';
        result = result + extra;
    } else {
        cout << "  extra = 0\n";
    }

    return result;
}

}  // namespace modified
