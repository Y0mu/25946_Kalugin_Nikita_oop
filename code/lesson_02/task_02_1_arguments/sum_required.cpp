#include "sum_required.h"

namespace required {

// Передача по значению: работаем с копиями x и y.
int SumByValue(int x, int y) {
    // Меняем копии — на исходные переменные это никак не влияет.
    x = x + 1;
    y = y + 1;
    return x + y;
}

// Передача по ссылке: x и y — это те же самые переменные, что и в main.
int SumByLink(int& x, int& y) {
    // Увеличиваем сами аргументы: изменения увидят снаружи.
    x = x + 1;
    y = y + 1;
    return x + y;
}

// Передача по константной ссылке: копирования нет, но менять x и y запрещено.
int SumByConstLink(const int& x, const int& y) {
    // x = x + 1;  // так не скомпилируется: x — константная ссылка
    return x + y;
}

// Задание 02.II. "Требуемая" функция.
int Sum(int& x, int& y) {
    x = x + 1;
    y = y + 1;
    return x + y;
}

}  // namespace required
