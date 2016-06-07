#include <stdio.h>
#include <stdlib.h>
#include "cvector.h"

int main(int argc, char **argv) {
    struct cvector_int_t vec;
    if (cvector_int_init(&vec) != 0) {
        perror("cvector_int_init");
        exit(1);
    }

    for (int i = 0; i < 10; ++i) {
        if (cvector_int_push(&vec, i) != 0) {
            perror("cvector_int_push");
            break;
        }
    }

    size_t size = cvector_int_size(&vec);
    if (size) {
        const int *itr = cvector_int_front(&vec);
        for (size_t i = 0; i < size; ++i, ++itr) {
            printf("%d\n", *itr);
        }
    }

    if (cvector_int_destroy(&vec) != 0) {
        perror("cvector_int_destroy");
        exit(1);
    }
    
    return 0;
}
