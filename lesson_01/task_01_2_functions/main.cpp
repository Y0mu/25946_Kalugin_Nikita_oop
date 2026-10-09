// Задание 01.II. Функции и организация кода.
// Точка входа: значения вводим с клавиатуры, вызываем обе функции
// ("требуемую" и "модифицированную") и сравниваем результаты.

#include "sum_required.h"
#include "sum_modified.h"

#include <iostream>

// Чтобы не писать std:: перед каждым именем из стандартной библиотеки.
using namespace std;

int main() {
    int x = 0;
    int y = 0;

    cout << "Enter two integers: ";
    cin >> x >> y;

    PrintTitle("required function");
    cout << "Sum(" << x << ", " << y << ") = " << Sum(x, y) << '\n';

    PrintTitle("modified function");
    cout << "ModifiedSum(" << x << ", " << y << ") = " << ModifiedSum(x, y) << '\n';

    // Вызовем ещё раз: видно, что добавка появляется случайно.
    cout << "ModifiedSum(" << x << ", " << y << ") = " << ModifiedSum(x, y) << '\n';

    return 0;
}
