// Задание 5.II. main.cpp не изменился, но библиотека теперь в поддиректории my_lib.
// Благодаря target_include_directories(mylib PUBLIC ...) заголовки подключаются
// по имени, без путей вида "my_lib/my_lib.h".

#include "my_lib.h"
#include "my_random.h"

#include <iostream>

// Чтобы не писать std:: перед каждым именем из стандартной библиотеки.
using namespace std;

int main() {
    int x = 0;
    int y = 0;

    cout << "Enter two integers: ";
    cin >> x >> y;

    cout << "my_lib::Sum(" << x << ", " << y << ") = "
              << my_lib::Sum(x, y) << '\n';

    cout << "my_random::RandomSum(" << x << ", " << y << ") = "
              << my_random::RandomSum(x, y) << '\n';

    cout << "my_random::RandomSumInRange(" << x << ", " << y << ", -20, 20) = "
              << my_random::RandomSumInRange(x, y, -20, 20) << '\n';

    cout << "library version: " << my_lib::Version() << '\n';

    return 0;
}
