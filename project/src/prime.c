#include "prime.h"

#define YES 1
#define NO  0

_Bool prime(int const num) {
    int counter = 0;
    for (int i = 2; (i*i) < num; ++i) {
        if (num % i == 0) ++counter;
    }
    if ((counter == 0) && (num > 1))
        return YES;
    else
        return NO;
}
