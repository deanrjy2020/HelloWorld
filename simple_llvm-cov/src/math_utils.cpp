#include "math_utils.h"

int add(int a, int b) {
    return a + b;
}

// 故意没有cover
int minus(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    if (a == 0 || b == 0)
        return 0;
    return a * b;
}
