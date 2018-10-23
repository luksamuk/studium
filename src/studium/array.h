#ifndef ST_ARRAY_H
#define ST_ARRAY_H

#include <stdlib.h>

#define ST_ARRAY_INITIAL_ELEMENTS 512

typedef size_t st_entity_t;

// Growable array structure
typedef struct ST_ARRAY {
    void*  elements;
    size_t element_size;
    size_t array_size;
    size_t num_elements;
} st_array;

st_array st_array_new(size_t element_size);
int      st_array_grow(st_array* array, size_t new_size);
int      st_array_destroy(st_array* array);
/* int      st_array_add(st_array* array, size_t* out, void* element); */
void*    st_array_get(st_array* array, size_t index);
int      st_array_put(st_array* array, size_t n, void* element);

#endif // ST_ARRAY_H
