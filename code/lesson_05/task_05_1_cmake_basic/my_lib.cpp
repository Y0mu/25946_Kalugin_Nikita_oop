#include "my_lib.h"

namespace my_lib {

// "Требуемая" функция: просто складываем два числа.
int Sum(int x, int y) {
    return x + y;
}

int Version() {
    // Версия 1 — первая сборка библиотеки в задании 5.I.
    return 1;
}

}  // namespace my_lib
