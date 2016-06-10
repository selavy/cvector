#ifndef CVECTOR_LONG__H_
#define CVECTOR_LONG__H_

#include <stddef.h>

struct cvector_long_t {
    // dynamically sized array of `long`s that guarantees
    // contiguous memory.
    long *buf;
    size_t size;
    size_t capacity;
};

typedef int (*cvector_long_finalizer_t)(long *elem);
// function pointer to cleanup elements if needed

int cvector_long_init(struct cvector_long_t *vec);
// initialize `vec` which must not be null.
// allocates starting buffer of size 8.
// returns 0 if successful.

int cvector_long_init_ex(struct cvector_long_t *vec, size_t init_capacity);
// initialize `vec` which must not be null.
// allocates starting buffer with size `init_capacity` * sizeof(long)

int cvector_long_push(struct cvector_long_t *vec, long elem);
// push `elem` onto `vec`.  may allocate a new buffer, move elements,
// and deallocate buffer.

void cvector_long_pop_back(struct cvector_long_t *vec);
// remove the last element in `vec`, which must not be empty

int cvector_long_pop_back_ex(struct cvector_long_t *vec, cvector_long_finalizer_t finalizer);
// remove the last element in `vec` and pass it to `finalizer` to destroy.
// `finalizer` must not be null.
// returns result from `finalizer`

size_t cvector_long_size(const struct cvector_long_t *vec);
// return the current number of elements in `vec`.
// `vec` must not be null

size_t cvector_long_capacity(const struct cvector_long_t *vec);
// return the capacity (number of elements allocated in buffer) of `vec`.
// `vec` must not be null

long *cvector_long_front(struct cvector_long_t *vec);
// return a pointer to the first element in `vec` which must not
// be null.  returns null if `vec` is empty.

int cvector_long_destroy(struct cvector_long_t *vec);
// deallocate memory allocated in `vec`.
// returns 0 if successful.

int cvector_long_destroy_ex(struct cvector_long_t *vec, cvector_long_finalizer_t finalizer);
// deallocate buffer in `vec`.  call `finalizer` on each element.
// neither `vec` or `finalizer` can be null.

#endif // CVECTOR_LONG__H_