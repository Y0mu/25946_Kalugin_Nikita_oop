#pragma once

// Задание 5.V. "Модифицированная" функция (с рандомом), тоже шаблонная.
// Как и my_lib.h, лежит в директории include/my_lib — так проект выглядит
// аккуратно: заголовки отдельно, реализации отдельно.

#include <random>

// Чтобы не писать std:: перед каждым именем из стандартной библиотеки.
using namespace std;

namespace my_random {

// ---- "Модифицированная" функция -------------------------------------------
// Складывает x и y и в половине случаев прибавляет случайную добавку.
// Вероятность задаём явно через bernoulli_distribution(0.5) — это
// стандартный способ бросить "честную монетку".
// Добавка приводится к типу T, поэтому функция работает и с int, и с double.
template <typename T>
T RandomSum(const T& x, const T& y) {
    // static — чтобы состояние генератора сохранялось между вызовами.
    static mt19937 generator{ random_device{}() };

    // Монетка: true с вероятностью 0.5.
    static bernoulli_distribution coin{ 0.5 };

    // Добавка — случайное целое, приведённое к типу T.
    static uniform_int_distribution<int> addition{ 0, 99 };

    T result = x + y;

    if (coin(generator)) {
        result = result + static_cast<T>(addition(generator));
    }

    return result;
}

// Вариант шаблона с двумя параметрами: аргументы одного типа T,
// а добавка — другого типа TModifier:
//   RandomSum<double, int>(2.5, 3.0, 2)
template <typename T, typename TModifier>
T RandomSum(const T& x, const T& y, const TModifier& extra) {
    return static_cast<T>(x + y + extra);
}

}  // namespace my_random
