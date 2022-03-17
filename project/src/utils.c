#include "utils.h"
#include <stddef.h>
#include <stdio.h>


size_t timer_from(short int from) {
    size_t counter = 0;
    for (short int i = from; i >= 0; --i) {
        if (i == 0) {
            printf("%d\n", i); 
            ++counter;
            break;
        }
         ++counter;
         printf("%d ", i);       
    }
    return counter;
}

// DO: Implement `power of` function
/*
int custom_pow(int base, int power) {
    return 0;
}git
*/
