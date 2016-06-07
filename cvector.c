#include "cvector.h"
#include <stdlib.h>
#include <string.h>

int cvector_int_init(struct cvector_int_t *vec) {
    vec->size = 0;
    vec->capacity = 8;
    /* TODO: replace with allocator */    
    vec->buf = malloc(sizeof(*vec->buf) * vec->capacity);
    return !vec->buf;
}

int cvector_int_init_ex(struct cvector_int_t *vec, size_t init_capacity) {
    vec->size = 0;
    vec->capacity = init_capacity;
    /* TODO: replace with allocator */    
    vec->buf = malloc(sizeof(int) * vec->capacity);
    return !vec->buf;
}

int cvector_int_push(struct cvector_int_t *vec, CVECTOR_TYPE elem) {
    if (vec->size > vec->capacity) {
        /* TODO: replace with allocator */
        /* TODO: multiple by 1.5 instead of doubling? */
        CVECTOR_TYPE *newbuf  = realloc(vec->buf, vec->capacity * 2);
        if (!newbuf) return 1;
        vec->capacity *= 2;
        vec->buf = newbuf;
    }
    memcpy(&vec->buf[vec->size++], &elem, sizeof(elem));
    return 0;
}

size_t cvector_int_size(struct cvector_int_t *vec) {
    return vec->size;
}

size_t cvector_int_capacity(struct cvector_int_t *vec) {
    return vec->capacity;
}

CVECTOR_TYPE *cvector_int_front(struct cvector_int_t *vec) {
    return &vec->buf[0];
}

int cvector_int_destroy(struct cvector_int_t *vec) {
    /* TODO: replace with destructor */
    if (vec->capacity) {
        free(vec->buf);
    }
    return 0;
}
