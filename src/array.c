#include "studium/array.h"
#include "studium/macros.h"
#include <string.h>
#include <stdlib.h>

/* ========================================================================== */
/*                                  st_array                                  */
/* ========================================================================== */

st_array
st_array_new(size_t element_size)
{
    st_array array;
    array.element_size = element_size;
    array.array_size   = ST_ARRAY_INITIAL_ELEMENTS;
    array.num_elements = 0;
    size_t sz_elements = element_size * ST_ARRAY_INITIAL_ELEMENTS;
    array.elements     = malloc(sz_elements);
    // TODO: we do not expect that, but malloc may fail!
    memset(array.elements, 0, sz_elements);
    return array;
}

int
st_array_grow(st_array* array, size_t new_size)
{
    if(!array) {
        st_log_err("attempt to perform operation on NULL reference to array");
        return 1;
    } else if(new_size < array->array_size) {
        st_log_err("invalid attempt to shrink array");
        return 1;
    } else if(new_size == array->array_size) {
        // Do nothing
        st_log_warn("attempt to increase array size with no size difference");
        return 0;
    }

    void* new_location = realloc(array->elements,
                                 array->element_size * new_size);
    if(!new_location) {
        st_log_err("cannot increase array: out of memory");
        return 1;
    }

    memset(new_location + array->array_size, 0, (new_size - array->array_size));
    array->elements   = new_location;
    array->array_size = new_size;
    return 0;
}

int
st_array_destroy(st_array* array)
{
    if(!array) {
        st_log_err("attempt to perform operation on NULL reference to array");
        return 1;
    } else if(!array->elements) {
        // This array was never used or has already been destroyed, somehow
        return 0;
    }
    free(array->elements);
    memset(array, 0, sizeof(st_array));
    return 0;
}

#define __st_array_check_avail(array)           \
    ((array->num_elements < array->array_size))

#define __st_array_put_at(array, index, element_ptr)            \
    memcpy((array->elements + (index * array->element_size)),   \
           element_ptr, array->element_size);                   \
    array->num_elements++;

static inline int
__st_array_grow_if_needed(st_array* array)
{
    if(!__st_array_check_avail(array)) {
        st_log_warn("attempt to grow array for adding more elements");
        if(st_array_grow(array, array->array_size * 2)) {
            st_log_err("cannot add element to array: out of memory");
            return 1;
        }
    }
    return 0;
}

/* int */
/* st_array_add(st_array* array, size_t* out, void* element) */
/* { */
/*     if(!array) { */
/*      st_log_err("attempt to perform operation on NULL reference to array"); */
/*      return 1; */
/*     } else if(!element) { */
/*      st_log_err("cannot add a NULL element to array"); */
/*      return 1; */
/*     } */

/*     // If our array is full, make it grow */
/*     if(__st_array_grow_if_needed(array)) */
/*      return 1; */

/*     size_t index = array->num_elements; */
/*     __st_array_put_at(array, index, element); */
/*     *out = index; */
/*     return 0; */
/* } */

void*
st_array_get(st_array* array, size_t index)
{
    if(!array) {
        st_log_err("attempt to perform operation on NULL reference to array");
        return NULL;
    }
    return (array->elements) + (index * array->element_size);
}

int
st_array_put(st_array* array, size_t n, void* element)
{
    if(!array) {
        st_log_err("attempt to perform operation on NULL reference to array");
        return 1;
    } else if(!element) {
        st_log_err("cannot add a NULL element to array");
        return 1;
    }

    // If our array is full, make it grow
    if(__st_array_grow_if_needed(array))
        return 1;

    __st_array_put_at(array, n, element);
    return 0;
}
