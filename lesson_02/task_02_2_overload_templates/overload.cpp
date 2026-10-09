#include "overload.h"

// Перегрузка по количеству аргументов.
int Sum(int x, int y, int z) {
    return x + y + z;
}

// Перегрузка по типам аргументов.
double Sum(int x, double y) {
    return x + y;
}

double Sum(double x, int y) {
    return x + y;
}

double Sum(double x, double y) {
    return x + y;
}
