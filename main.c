#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cvector.h"

void print_cvector(struct cvector_int_t *vec) {
    assert(vec);
    puts("Printing vector...");
    const size_t size = cvector_int_size(vec);
    if (size) {
        const int *itr = cvector_int_front(vec);
        for (size_t i = 0; i < size; ++i, ++itr) {
            printf("%d ", *itr);
        }
    }
    printf("\n");
}

int main(int argc, char **argv) {
    struct cvector_int_t vec;
    if (cvector_int_init(&vec) != 0) {
        perror("cvector_int_init");
        exit(1);
    }

    puts("Before inserts...");
    print_cvector(&vec);

    for (int i = 0; i < 20; ++i) {
        if (cvector_int_push(&vec, i) != 0) {
            perror("cvector_int_push");
            break;
        }
    }
    puts("After inserts...");
    print_cvector(&vec);
    
    for (int i = 0; i < 10; ++i) {
        cvector_int_pop_back(&vec);
    }
    puts("After popping 10 elements...");
    print_cvector(&vec);

    if (cvector_int_destroy(&vec) != 0) {
        perror("cvector_int_destroy");
        exit(1);
    }
    
    return 0;
}
