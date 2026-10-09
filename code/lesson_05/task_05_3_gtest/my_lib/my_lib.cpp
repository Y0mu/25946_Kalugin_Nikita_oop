#include "my_lib.h"

#include <random>

// Чтобы не писать std:: перед каждым именем из стандартной библиотеки.
using namespace std;

namespace my_lib {

int Sum(int x, int y) {
    return x + y;
}

int Version() {
    // Версия 3 — проект с тестами GoogleTest (задание 5.III).
    return 3;
}

}  // namespace my_lib

namespace my_random {

namespace {

// Один генератор на всю библиотеку.
mt19937& Generator() {
    static mt19937 generator{ random_device{}() };
    return generator;
}

// "Монетка": true с вероятностью 50%.
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
