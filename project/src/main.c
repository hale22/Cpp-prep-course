#include "utils.h"
#include "prime.h"
#include "recursion.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define ERR_ARGS_COUNT  (-1)
#define ERR_WRONG_FLG   (-2)

#define TST_FOO_FIX     1
#define TST_FOO_IMPL    2
#define TST_MOD_IMPL    3
#define TST_MOD_REC     4

int main(int argc, const char** argv) {
    if (argc < 3) {
        return ERR_ARGS_COUNT;
    }
    int test_case = strtol(argv[1], NULL, 10);
    const char* data;
    data = argv[2];

    switch (test_case) {
        case TST_FOO_FIX: {
            int to = strtol(data, NULL, 10);
            size_t ticks_count = timer_from(to);
            printf("%zu", ticks_count);
            break;
        }
        case TST_FOO_IMPL: {
            if (argc == 4) {
                int base = strtol(data, NULL, 10);
                int pow = strtol(argv[3], NULL, 10);
                int res = custom_pow(base, pow);
                printf("%i\n", res);
            } else {
                return ERR_ARGS_COUNT;
            }
            break;
        }
        case TST_MOD_IMPL: {
            int num = strtol(data, NULL, 10);
            _Bool answer = prime(num);
            printf("%d\n", answer);
            break;
        }
        case TST_MOD_REC: {
            int num = strtol(data, NULL, 10);
            recur(num);
            break;
        }
        default: {
            return ERR_WRONG_FLG;
        }
    }
}
