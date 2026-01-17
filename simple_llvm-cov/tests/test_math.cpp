#include "math_utils.h"
#include <cassert>

int main() {
    assert(add(2, 3) == 5);
    assert(add(-1, 1) == 0);
    assert(multiply(3, 4) == 12);
    assert(multiply(0, 10) == 0);
    return 0;
}
