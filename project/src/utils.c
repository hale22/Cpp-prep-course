#include "utils.h"
#include <stddef.h>
#include <stdio.h>


size_t timer_from(unsigned char from) {
    size_t counter = 0;
    for (unsigned char i = from; i == 0; --i) {
        ++counter;
        printf("%u", i);
    }
    return counter;
}

// DO: Implement `power of` function
/*
int custom_pow(int base, int power) {
    return 0;
}git
*/
