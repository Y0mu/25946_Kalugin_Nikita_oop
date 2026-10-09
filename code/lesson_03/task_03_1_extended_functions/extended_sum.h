#pragma once

#include <iostream>
#include <random>

// Чтобы не писать std:: перед каждым именем из стандартной библиотеки.
using namespace std;

// TResult — тип результата, T1 и T2 — типы аргументов, T3 — тип добавки.
// Складываем x + y (+ extra, если его передали) и приводим результат к TResult.
template <typename TResult, typename T1, typename T2, typename T3 = T1>
TResult ExtendedSum(const T1& x, const T2& y, const T3& extra = T3{}) {
    TResult result = static_cast<TResult>(x + y + extra);
    return result;
}

// ---- Расширенная модифицированная функция ---------------------------------
// Работает так же, но в половине случаев прибавляет случайное число.
// Случайное число берём в диапазоне, который передали аргументами (по умолчанию 0..99).
// verbose = true печатает добавку на экран; его отключают,
// когда эту функцию вызывают в цикле и вывод мешает.
template <typename TResult, typename T1, typename T2, typename T3 = T1>
TResult ExtendedModifiedSum(const T1& x, const T2& y,
                            int rangeMin = 0, int rangeMax = 99,
                            bool verbose = true) {
    // static — чтобы состояние генератора сохранялось между вызовами.
    static mt19937 generator{ random_device{}() };

    uniform_int_distribution<int> coin{ 0, 1 };

    TResult result = static_cast<TResult>(x + y);

    if (coin(generator) == 1) {
        uniform_int_distribution<int> addition{ rangeMin, rangeMax };
        T3 extra = static_cast<T3>(addition(generator));
        if (verbose) {
            cout << "  extra = " << extra << '\n';
        }
        result = result + static_cast<TResult>(extra);
    } else {
        if (verbose) {
            cout << "  extra = 0\n";
        }
    }

    return result;
}
