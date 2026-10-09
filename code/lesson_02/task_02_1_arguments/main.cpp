// Задания 02.I и 02.II.
// Смотрим, чем отличаются передача по значению, по ссылке и по константной ссылке,
// а потом вызываем "требуемую" и "модифицированную" функции с одинаковыми сигнатурами.

#include "sum_required.h"

#include <iostream>

// Чтобы не писать std:: перед каждым именем из стандартной библиотеки.
using namespace std;

int main() {
    int a = 0;
    int b = 0;

    cout << "Enter two integers: ";
    cin >> a >> b;

    // 1) Передача по значению.
    //    Внутри функции x и y увеличились, но a и b остались прежними.
    int valueResult = required::SumByValue(a, b);
    cout << "by value:       result = " << valueResult
              << ", a = " << a << ", b = " << b << '\n';

    // 2) Передача по константной ссылке.
    //    Копий нет, но менять аргументы нельзя — и a, b, конечно, не изменились.
    int constResult = required::SumByConstLink(a, b);
    cout << "const link:     result = " << constResult
              << ", a = " << a << ", b = " << b << '\n';

    // 3) Передача по ссылке: изменения аргументов видны снаружи.
    int linkResult = required::SumByLink(a, b);
    cout << "by link:        result = " << linkResult
              << ", a = " << a << ", b = " << b << '\n';

    // 4) Задание 02.II. Одинаковые сигнатуры, разное поведение.
    //    Значения вернём к исходным, чтобы сравнение было честным.
    cout << "Enter two integers again: ";
    cin >> a >> b;

    int requiredA = a;
    int requiredB = b;
    cout << "required::Sum   = "
              << required::Sum(requiredA, requiredB)
              << ", a = " << requiredA << ", b = " << requiredB << '\n';

    int modifiedA = a;
    int modifiedB = b;
    cout << "modified::Sum   = "
              << modified::Sum(modifiedA, modifiedB)
              << ", a = " << modifiedA << ", b = " << modifiedB << '\n';

    return 0;
}
