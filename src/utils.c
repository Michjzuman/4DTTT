#include "utils.h"

I64 power(I64 a, U64 b) {
    if (b == 0) return 1;
    I64 r = a;
    for (U64 i = 1; i < b; i++) r *= a;
    return r;
}
