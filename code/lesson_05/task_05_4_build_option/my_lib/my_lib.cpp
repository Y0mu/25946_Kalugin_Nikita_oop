#include "my_lib.h"

#include <random>

// Чтобы не писать std:: перед каждым именем из стандартной библиотеки.
using namespace std;

namespace my_lib {

int Sum(int x, int y) {
    return x + y;
}

int Version() {
    // Версия 4 — проект с опцией сборки тестов (задание 5.IV).
    return 4;
}

}  // namespace my_lib

namespace my_random {

namespace {

mt19937& Generator() {
    static mt19937 generator{ random_device{}() };
    return generator;
}

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
