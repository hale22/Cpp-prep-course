#include "prime.h"

#define YES 1
#define NO  0

_Bool prime(int const num) {
    int counter = 0;
    for (int i = num - 1; i > 1; --i) {
        if (num % i != 0) ++counter;
    }
    if (counter == num - 2)
        return YES;
    else
        return NO;
}
