// Задание 5.III. Обычная программа, которая использует библиотеку.
// Она нужна, чтобы показать: библиотека работает и сама по себе, и в тестах.

#include "my_lib.h"

#include <iostream>

// Чтобы не писать std:: перед каждым именем из стандартной библиотеки.
using namespace std;

int main() {
    int x = 0;
    int y = 0;

    cout << "Enter two integers: ";
    cin >> x >> y;

    cout << "my_lib::Sum(" << x << ", " << y << ") = " << my_lib::Sum(x, y) << '\n';
    cout << "my_random::RandomSum(" << x << ", " << y << ") = "
              << my_random::RandomSum(x, y) << '\n';
    cout << "library version: " << my_lib::Version() << '\n';

    return 0;
}
