#include "my_lib/my_lib.h"

namespace my_lib {

// Обычная функция: раз шаблоны живут в заголовке, здесь остаётся то,
// что не зависит от типа.
int Version() {
    // Версия 5 — шаблонная библиотека (задание 5.V).
    return 5;
}

}  // namespace my_lib
