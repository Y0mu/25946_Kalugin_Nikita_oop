#pragma once

// Задание 5.III. Библиотека та же, что и в 5.II, плюс подключены тесты GoogleTest.
// Функции намеренно сделаны простыми: их легко проверять в тестах.

namespace my_lib {

// Складывает два целых числа.
int Sum(int x, int y);

// Номер версии библиотеки.
int Version();

}  // namespace my_lib

namespace my_random {

// Складывает два числа и в половине случаев прибавляет случайную добавку.
int RandomSum(int x, int y);

// То же самое, но добавка берётся из диапазона [rangeMin, rangeMax].
int RandomSumInRange(int x, int y, int rangeMin, int rangeMax);

}  // namespace my_random
