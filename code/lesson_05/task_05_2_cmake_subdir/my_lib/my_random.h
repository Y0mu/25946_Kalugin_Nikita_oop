#pragma once

// Задание 5.II. "Модифицированная" функция с рандомом — тоже часть библиотеки.

namespace my_random {

// Складывает два числа и в половине случаев прибавляет случайную добавку.
int RandomSum(int x, int y);

// То же самое, но добавка берётся из диапазона [rangeMin, rangeMax].
int RandomSumInRange(int x, int y, int rangeMin, int rangeMax);

}  // namespace my_random
