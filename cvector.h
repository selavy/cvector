#ifndef CVECTOR__H_
#define CVECTOR__H_

#include <stddef.h>

/* TODO: define this type before including file */
#define CVECTOR_TYPE int

struct cvector_int_t {
    // dynamically sized array that guarantees contiguous memory
    
    CVECTOR_TYPE *buf;
    size_t size;
    size_t capacity;
};

int cvector_int_init(struct cvector_int_t *vec);
// initialize `vec` which must not be null.
// allocates starting buffer of size 8.
// returns 0 if successful.

int cvector_int_init_ex(struct cvector_int_t *vec, size_t init_capacity);
// initialize `vec` which must not be null.
// allocates starting buffer with size `init_capacity` * sizeof(CVECTOR_TYPE)

int cvector_int_push(struct cvector_int_t *vec, CVECTOR_TYPE elem);
// push `elem` onto `vec`.  may allocate a new buffer, move elements,
// and deallocate buffer.

size_t cvector_int_size(struct cvector_int_t *vec);
// return the current number of elements in `vec`.
// `vec` must not be null

size_t cvector_int_capacity(struct cvector_int_t *vec);
// return the capacity (number of elements allocated in buffer) of `vec`.
// `vec` must not be null

CVECTOR_TYPE *cvector_int_front(struct cvector_int_t *vec);
// return a pointer to the first element in `vec` which must not
// be null.  returns null if `vec` is empty.

int cvector_int_destroy(struct cvector_int_t *vec);
// deallocate memory allocated in `vec`.
// returns 0 if successful.

#endif // CVECTOR__H_
