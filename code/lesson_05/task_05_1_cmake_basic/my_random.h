#pragma once

// Задание 5.I. "Модифицированная" функция (с рандомом) в своём пространстве имён.
// Отдельные файлы: объявление здесь, реализация в my_random.cpp.
// Обе функции (Sum и RandomSum) собираются в одну библиотеку mylib.

namespace my_random {

// Складывает два числа и в половине случаев прибавляет случайную добавку.
int RandomSum(int x, int y);

// То же самое, но случайная добавка берётся из диапазона [rangeMin, rangeMax].
int RandomSumInRange(int x, int y, int rangeMin, int rangeMax);

}  // namespace my_random
