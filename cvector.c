#include "cvector.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct cvector_int_t {
    CVECTOR_TYPE *buf;
    size_t size;
    size_t capacity;
};

int cvector_int_init(struct cvector_int_t *vec) {
    assert(vec);
    vec->size = 0;
    vec->capacity = 8;
    /* TODO: replace with allocator */    
    vec->buf = malloc(sizeof(*vec->buf) * vec->capacity);
    return !vec->buf;
}

int cvector_int_init_ex(struct cvector_int_t *vec, size_t init_capacity) {
    assert(vec);
    vec->size = 0;
    vec->capacity = init_capacity;
    /* TODO: replace with allocator */    
    vec->buf = malloc(sizeof(int) * vec->capacity);
    return !vec->buf;
}

int cvector_int_push(struct cvector_int_t *vec, CVECTOR_TYPE elem) {
    assert(vec);
    if (vec->size > vec->capacity) {
        /* TODO: replace with allocator */
        /* TODO: multiple by 1.5 instead of doubling? */
        CVECTOR_TYPE *newbuf  = realloc(vec->buf, vec->capacity * 2 * sizeof(*vec->buf));
        if (!newbuf) return 1;
        vec->capacity *= 2;
        vec->buf = newbuf;
    }
    memcpy(&vec->buf[vec->size++], &elem, sizeof(elem));
    return 0;
}

void cvector_int_pop_back(struct cvector_int_t *vec) {
    assert(vec);
    assert(vec->size);
    --vec->size;
}

int cvector_int_pop_back_ex(struct cvector_int_t *vec, cvector_int_finalizer_t finalizer) {
    assert(vec);
    assert(vec->size);
    assert(finalizer);
    return finalizer(&vec->buf[--vec->size]);
}

size_t cvector_int_size(const struct cvector_int_t *vec) {
    assert(vec);
    return vec->size;
}

size_t cvector_int_capacity(const struct cvector_int_t *vec) {
    assert(vec);
    return vec->capacity;
}

CVECTOR_TYPE *cvector_int_front(struct cvector_int_t *vec) {
    assert(vec);
    assert(vec->size);
    return &vec->buf[0];
}

int cvector_int_destroy(struct cvector_int_t *vec) {
    assert(vec);
    /* TODO: replace with destructor */
    if (vec->capacity) {
        free(vec->buf);
    }
    return 0;
}

int cvector_int_destroy_ex(struct cvector_int_t *vec, cvector_int_finalizer_t finalizer) {
    assert(vec);
    int ret = 0;
    if (vec->capacity) {
        for (size_t i = 0; i < vec->size; ++i) {
            if (finalizer(&vec->buf[i]) != 0) {
                ret = 1;
                break;
            }
        }
        /* still need to deallocate buffer even if finalizer fails? */
        free(vec->buf);
    }
    return ret;
}
