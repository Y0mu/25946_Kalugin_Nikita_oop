// Задание 3.I (1). "Расширенная" функция.
// Проверяем оба случая из задания:
//   1) вход int,    результат double (в задании сказано float — идея та же);
//   2) вход double, результат int.
// Плюс демонстрируем "расширенную модифицированную" (с рандомом) функцию.

#include "extended_sum.h"

#include <iostream>

// Чтобы не писать std:: перед каждым именем из стандартной библиотеки.
using namespace std;

int main() {
    int intValue1 = 0;
    int intValue2 = 0;
    double doubleValue1 = 0.0;
    double doubleValue2 = 0.0;

    cout << "Enter two integers: ";
    cin >> intValue1 >> intValue2;
    cout << "Enter two doubles: ";
    cin >> doubleValue1 >> doubleValue2;

    cout << "\n== Расширенная заданная функция ==\n";

    // Вход int, результат double.
    // Типы указываем явно: <результат, тип 1-го аргумента, тип 2-го аргумента>.
    double doubleResult = ExtendedSum<double, int, int>(intValue1, intValue2);
    cout << "ExtendedSum<double, int, int>(" << intValue1 << ", " << intValue2
              << ") = " << doubleResult << '\n';

    // Вход double, результат int.
    // Обратите внимание: дробная часть при приведении к int просто отбрасывается.
    int intResult = ExtendedSum<int, double, double>(doubleValue1, doubleValue2);
    cout << "ExtendedSum<int, double, double>(" << doubleValue1 << ", " << doubleValue2
              << ") = " << intResult << '\n';

    // Третий аргумент (добавка) тоже поддерживается.
    cout << "ExtendedSum<double, int, int>(x, y, 10) = "
              << ExtendedSum<double, int, int>(intValue1, intValue2, 10) << '\n';

    // Один из аргументов приводим к double — тогда результат получается точнее.
    cout << "ExtendedSum<double, double, int>(x, y) = "
              << ExtendedSum<double, double, int>(static_cast<double>(intValue1), intValue2) << '\n';

    cout << "\n== Расширенная модифицированная функция (с рандомом) ==\n";
    cout << "ExtendedModifiedSum<double, int, int>(" << intValue1 << ", " << intValue2
              << ") = " << ExtendedModifiedSum<double, int, int>(intValue1, intValue2,
                                                                 -20, 20) << '\n';
    cout << "ExtendedModifiedSum<double, double, double>(" << doubleValue1 << ", "
              << doubleValue2 << ") = "
              << ExtendedModifiedSum<double, double, double>(doubleValue1, doubleValue2,
                                                             -20, 20) << '\n';

    return 0;
}
