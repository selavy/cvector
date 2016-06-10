#!/usr/bin/env python

from __future__ import print_function
import sys
import optparse

def gen_guard(ctype):
    return 'CVECTOR_{type}__H_'.format(type=ctype.upper())

HEADER = '''#ifndef {guard}
#define {guard}

#include <stddef.h>

struct cvector_{type}_t {{
    // dynamically sized array of `{type}`s that guarantees
    // contiguous memory.
    {type} *buf;
    size_t size;
    size_t capacity;
}};

typedef int (*cvector_{type}_finalizer_t)({type} *elem);
// function pointer to cleanup elements if needed

int cvector_{type}_init(struct cvector_{type}_t *vec);
// initialize `vec` which must not be null.
// allocates starting buffer of size 8.
// returns 0 if successful.

int cvector_{type}_init_ex(struct cvector_{type}_t *vec, size_t init_capacity);
// initialize `vec` which must not be null.
// allocates starting buffer with size `init_capacity` * sizeof({type})

int cvector_{type}_push(struct cvector_{type}_t *vec, {type} elem);
// push `elem` onto `vec`.  may allocate a new buffer, move elements,
// and deallocate buffer.

void cvector_{type}_pop_back(struct cvector_{type}_t *vec);
// remove the last element in `vec`, which must not be empty

int cvector_{type}_pop_back_ex(struct cvector_{type}_t *vec, cvector_{type}_finalizer_t finalizer);
// remove the last element in `vec` and pass it to `finalizer` to destroy.
// `finalizer` must not be null.
// returns result from `finalizer`

size_t cvector_{type}_size(const struct cvector_{type}_t *vec);
// return the current number of elements in `vec`.
// `vec` must not be null

size_t cvector_{type}_capacity(const struct cvector_{type}_t *vec);
// return the capacity (number of elements allocated in buffer) of `vec`.
// `vec` must not be null

{type} *cvector_{type}_front(struct cvector_{type}_t *vec);
// return a pointer to the first element in `vec` which must not
// be null.  returns null if `vec` is empty.

int cvector_{type}_destroy(struct cvector_{type}_t *vec);
// deallocate memory allocated in `vec`.
// returns 0 if successful.

int cvector_{type}_destroy_ex(struct cvector_{type}_t *vec, cvector_{type}_finalizer_t finalizer);
// deallocate buffer in `vec`.  call `finalizer` on each element.
// neither `vec` or `finalizer` can be null.

#endif // {guard}'''

def gen_header(ctype):
    return HEADER.format(type=ctype, guard=gen_guard(ctype))

IMPLEMENTATION = '''#include "{header_name}.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int cvector_{type}_init(struct cvector_{type}_t *vec) {{
    assert(vec);
    vec->size = 0;
    vec->capacity = 8;
    /* TODO: replace with allocator */    
    vec->buf = malloc(sizeof(*vec->buf) * vec->capacity);
    return !vec->buf;
}}

int cvector_{type}_init_ex(struct cvector_{type}_t *vec, size_t init_capacity) {{
    assert(vec);
    vec->size = 0;
    vec->capacity = init_capacity;
    /* TODO: replace with allocator */    
    vec->buf = malloc(sizeof({type}) * vec->capacity);
    return !vec->buf;
}}

int cvector_{type}_push(struct cvector_{type}_t *vec, {type} elem) {{
    assert(vec);
    if (vec->size > vec->capacity) {{
        /* TODO: replace with allocator */
        /* TODO: multiple by 1.5 instead of doubling? */
        {type} *newbuf  = realloc(vec->buf, vec->capacity * 2 * sizeof(*vec->buf));
        if (!newbuf) return 1;
        vec->capacity *= 2;
        vec->buf = newbuf;
    }}
    memcpy(&vec->buf[vec->size++], &elem, sizeof(elem));
    return 0;
}}

void cvector_{type}_pop_back(struct cvector_{type}_t *vec) {{
    assert(vec);
    assert(vec->size);
    --vec->size;
}}

int cvector_{type}_pop_back_ex(struct cvector_{type}_t *vec, cvector_{type}_finalizer_t finalizer) {{
    assert(vec);
    assert(vec->size);
    assert(finalizer);
    return finalizer(&vec->buf[--vec->size]);
}}

size_t cvector_{type}_size(const struct cvector_{type}_t *vec) {{
    assert(vec);
    return vec->size;
}}

size_t cvector_{type}_capacity(const struct cvector_{type}_t *vec) {{
    assert(vec);
    return vec->capacity;
}}

{type} *cvector_{type}_front(struct cvector_{type}_t *vec) {{
    assert(vec);
    assert(vec->size);
    return &vec->buf[0];
}}

int cvector_{type}_destroy(struct cvector_{type}_t *vec) {{
    assert(vec);
    /* TODO: replace with destructor */
    if (vec->capacity) {{
        free(vec->buf);
    }}
    return 0;
}}

int cvector_{type}_destroy_ex(struct cvector_{type}_t *vec, cvector_{type}_finalizer_t finalizer) {{
    assert(vec);
    int ret = 0;
    if (vec->capacity) {{
        for (size_t i = 0; i < vec->size; ++i) {{
            if (finalizer(&vec->buf[i]) != 0) {{
                ret = 1;
                break;
            }}
        }}
        /* still need to deallocate buffer even if finalizer fails? */
        free(vec->buf);
    }}
    return ret;
}}
'''

def gen_filename(ctype):
    return 'cvector_{type}'.format(type=ctype)

def gen_impl(ctype):
    return IMPLEMENTATION.format(
        type=ctype, header_name=gen_filename(ctype))

def get_opts():
    parser = optparse.OptionParser()
    parser.add_option('--type', help='Data type to store in vector (e.g. int)')
    options, args = parser.parse_args()

    if not options.type:
        print("--type required")
        sys.exit(0)
    
    return options

if __name__ == '__main__':
    opts = get_opts()
    ctype = opts.type
    header = gen_filename(ctype) + '.h'
    impl = gen_filename(ctype) + '.c'
    with open(header, 'w') as f:
        f.write(gen_header(ctype))
    print("Created file {}".format(header))
    with open(impl, 'w') as f:
        f.write(gen_impl(ctype))
    print("Created file {}".format(impl))

