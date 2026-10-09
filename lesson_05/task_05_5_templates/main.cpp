// Задание 5.V. Программа, которая пользуется шаблонной библиотекой.
// Видно, что одни и те же функции работают и с int, и с double,
// и даже с тремя аргументами.

#include "my_lib/my_lib.h"
#include "my_lib/my_random.h"

#include <iostream>
#include <string>

// Чтобы не писать std:: перед каждым именем из стандартной библиотеки.
using namespace std;

int main() {
    int x = 0;
    int y = 0;

    cout << "Enter two integers: ";
    cin >> x >> y;

    cout << "\n== Шаблон my_lib::Sum ==\n";
    cout << "Sum<int>(" << x << ", " << y << ") = " << my_lib::Sum<int>(x, y) << '\n';
    cout << "Sum(" << x << ", " << y << ") = " << my_lib::Sum(x, y)
              << "  (тип выведен автоматически)\n";
    cout << "Sum<double>(" << x << ".0, " << y << ".5) = "
              << my_lib::Sum<double>(static_cast<double>(x), y + 0.5) << '\n';
    cout << "Sum(x, y, 100) = " << my_lib::Sum(x, y, 100) << '\n';
    cout << "Sum<double, int, int>(" << x << ", " << y << ") = "
              << my_lib::Sum<double, int, int>(x, y)
              << "  (тип результата задан отдельно)\n";
    cout << "Sum<string>(\"a\", \"bcd\") = "
              << my_lib::Sum(string("a"), string("bcd")) << '\n';

    cout << "\n== Шаблон my_random::RandomSum ==\n";
    cout << "RandomSum<int>(" << x << ", " << y << ") = "
              << my_random::RandomSum<int>(x, y) << '\n';
    cout << "RandomSum<double>(" << x << ".5, " << y << ".5) = "
              << my_random::RandomSum<double>(x + 0.5, y + 0.5) << '\n';
    cout << "RandomSum<double, int>(" << x << ".5, " << y << ".5, 2) = "
              << my_random::RandomSum<double, int>(x + 0.5, y + 0.5, 2) << '\n';

    cout << "\nlibrary version: " << my_lib::Version() << '\n';

    return 0;
}
