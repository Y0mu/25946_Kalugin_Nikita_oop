// Задания 02.III и 02.IV.
// 02.III — показать, что функция умеет работать и с double;
// 02.IV  — переписать "требуемую" и "модифицированную" функции через шаблоны.

#include "functions.h"
#include "overload.h"

#include <iostream>
#include <string>

// Чтобы не писать std:: перед каждым именем из стандартной библиотеки.
using namespace std;

int main() {
    int x = 0;
    double z = 0.0;

    cout << "Enter an int and a double: ";
    cin >> x >> z;

    cout << "\n== Перегрузка функций ==\n";
    cout << "Sum(x, x, x)      = " << Sum(x, x, x) << '\n';
    cout << "Sum(x, z)         = " << Sum(x, z) << '\n';
    cout << "Sum(z, x)         = " << Sum(z, x) << '\n';
    cout << "Sum(z, z)         = " << Sum(z, z) << '\n';

    cout << "\n== Шаблоны: требуемая функция ==\n";
    // Тип указываем явно в угловых скобках.
    cout << "required::Sum<int>   = " << required::Sum<int>(x, x) << '\n';
    cout << "required::Sum<double>= " << required::Sum<double>(z, z) << '\n';
    // А здесь компилятор выведет тип сам по аргументам.
    cout << "required::Sum        = " << required::Sum(x, x) << '\n';
    cout << "required::Sum        = " << required::Sum(z, z) << '\n';
    // Один шаблон спокойно работает и со строками (у них тоже есть оператор +).
    cout << "required::Sum        = " << required::Sum<string>("a", "bcd") << '\n';

    cout << "\n== Шаблоны: модифицированная функция ==\n";
    cout << "modified::Sum<int>   = " << modified::Sum<int>(x, x) << '\n';
    cout << "modified::Sum<double>= " << modified::Sum<double>(z, z) << '\n';

    return 0;
}
