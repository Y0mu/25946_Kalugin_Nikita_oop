#include "my_lib.h"

namespace my_lib {

int Sum(int x, int y) {
    return x + y;
}

int Version() {
    // Версия 2 — библиотека вынесена в отдельную поддиректорию (задание 5.II).
    return 2;
}

}  // namespace my_lib
