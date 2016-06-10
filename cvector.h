#ifndef CVECTOR__H_
#define CVECTOR__H_

#include <stddef.h>

/* TODO: define this type before including file */
#define CVECTOR_TYPE int
//#define CVECTOR cvector_##CVECTOR_TYPE##_t
#define CVECTOR cvector_int_t
#define FINALIZER cvector_int_finalizer_t

//struct cvector_int_t {
struct cvector_int_t {
    // dynamically sized array that guarantees contiguous memory
    CVECTOR_TYPE *buf;
    size_t size;
    size_t capacity;
};

typedef int (*FINALIZER)(CVECTOR_TYPE *elem);
// function pointer to cleanup elements if needed

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

/* TODO: allow pass destructor? */
void cvector_int_pop_back(struct cvector_int_t *vec);
// remove the last element in `vec`, which must not be empty

int cvector_int_pop_back_ex(struct cvector_int_t *vec, FINALIZER finalizer);
// remove the last element in `vec` and pass it to `finalizer` to destroy.
// `finalizer` must not be null.
// returns result from `finalizer`

size_t cvector_int_size(const struct cvector_int_t *vec);
// return the current number of elements in `vec`.
// `vec` must not be null

size_t cvector_int_capacity(const struct cvector_int_t *vec);
// return the capacity (number of elements allocated in buffer) of `vec`.
// `vec` must not be null

CVECTOR_TYPE *cvector_int_front(struct cvector_int_t *vec);
// return a pointer to the first element in `vec` which must not
// be null.  returns null if `vec` is empty.

int cvector_int_destroy(struct cvector_int_t *vec);
// deallocate memory allocated in `vec`.
// returns 0 if successful.

int cvector_int_destroy_ex(struct cvector_int_t *vec, FINALIZER finalizer);
// deallocate buffer in `vec`.  call `finalizer` on each element.
// neither `vec` or `finalizer` can be null.

#endif // CVECTOR__H_
