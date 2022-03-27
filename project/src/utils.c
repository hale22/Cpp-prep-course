#include "utils.h"

#include <stddef.h>
#include <stdio.h>

size_t timer_from(int const from) {
    size_t counter = 0;
    for (int i = from; i >= 0; --i) {
        (i == 0) ? (++counter, printf("%d\n", i)) : (++counter, printf("%d ", i));
    }
    return counter;
}

int custom_pow(int const base, int const pow) {
    if (base == 0 || base == 1) {
        return base;
    } else if (pow == 0) {
        return 1;
    } else {
        int res = base;
        for (int i = pow - 1; i > 0; --i) {
            res*=base;
        }
        return res;
    }
}
