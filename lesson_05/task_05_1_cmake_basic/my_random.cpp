#include "my_random.h"

#include <random>

// Чтобы не писать std:: перед каждым именем из стандартной библиотеки.
using namespace std;

namespace my_random {

namespace {

// Один генератор на всю библиотеку: static, чтобы состояние сохранялось между вызовами.
mt19937& Generator() {
    static mt19937 generator{ random_device{}() };
    return generator;
}

// Бросаем "монетку": возвращает true с вероятностью 50%.
bool Coin() {
    static uniform_int_distribution<int> distribution{ 0, 1 };
    return distribution(Generator()) == 1;
}

}  // namespace

int RandomSum(int x, int y) {
    return RandomSumInRange(x, y, 0, 99);
}

int RandomSumInRange(int x, int y, int rangeMin, int rangeMax) {
    int result = x + y;

    if (Coin()) {
        uniform_int_distribution<int> addition{ rangeMin, rangeMax };
        result = result + addition(Generator());
    }

    return result;
}

}  // namespace my_random
