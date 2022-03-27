#include "recursion.h"

#include <stdio.h>

void recur(int num) {
    if (num == 1) {
            printf("%d", num);
            return;
    }
    if (num > 1) {
        recur(num - 1);
        printf(" %d", num);
        return;
    }
    if (num <= 0) {
        recur(num + 1);
        printf(" %d", num);
        return;
    }
}
