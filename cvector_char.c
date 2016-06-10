#include "cvector_char.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int cvector_char_init(struct cvector_char_t *vec) {
    assert(vec);
    vec->size = 0;
    vec->capacity = 8;
    /* TODO: replace with allocator */    
    vec->buf = malloc(sizeof(*vec->buf) * vec->capacity);
    return !vec->buf;
}

int cvector_char_init_ex(struct cvector_char_t *vec, size_t init_capacity) {
    assert(vec);
    vec->size = 0;
    vec->capacity = init_capacity;
    /* TODO: replace with allocator */    
    vec->buf = malloc(sizeof(char) * vec->capacity);
    return !vec->buf;
}

int cvector_char_push(struct cvector_char_t *vec, char elem) {
    assert(vec);
    if (vec->size > vec->capacity) {
        /* TODO: replace with allocator */
        /* TODO: multiple by 1.5 instead of doubling? */
        char *newbuf  = realloc(vec->buf, vec->capacity * 2 * sizeof(*vec->buf));
        if (!newbuf) return 1;
        vec->capacity *= 2;
        vec->buf = newbuf;
    }
    memcpy(&vec->buf[vec->size++], &elem, sizeof(elem));
    return 0;
}

void cvector_char_pop_back(struct cvector_char_t *vec) {
    assert(vec);
    assert(vec->size);
    --vec->size;
}

int cvector_char_pop_back_ex(struct cvector_char_t *vec, cvector_char_finalizer_t finalizer) {
    assert(vec);
    assert(vec->size);
    assert(finalizer);
    return finalizer(&vec->buf[--vec->size]);
}

size_t cvector_char_size(const struct cvector_char_t *vec) {
    assert(vec);
    return vec->size;
}

size_t cvector_char_capacity(const struct cvector_char_t *vec) {
    assert(vec);
    return vec->capacity;
}

char *cvector_char_front(struct cvector_char_t *vec) {
    assert(vec);
    assert(vec->size);
    return &vec->buf[0];
}

int cvector_char_destroy(struct cvector_char_t *vec) {
    assert(vec);
    /* TODO: replace with destructor */
    if (vec->capacity) {
        free(vec->buf);
    }
    return 0;
}

int cvector_char_destroy_ex(struct cvector_char_t *vec, cvector_char_finalizer_t finalizer) {
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
