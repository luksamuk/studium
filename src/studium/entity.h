#ifndef ENTITY_H
#define ENTITY_H

#include "studium/array.h"
#include "studium/stmath.h"

typedef size_t st_entity;

// Dummy components.
// Remove later.
typedef struct {
    st_vec3 p;
} st_pos_c;

typedef struct {
    st_mat4 model;
    st_mat4 view;
    st_mat4 projection;
} st_mvp_c;

typedef enum {
    ST_ENTITY_TAGS,
    ST_POSITION,
    ST_MVP
} st_component_t;

//typedef size_t st_component_t;

// Structure of Arrays approach
typedef struct {
    st_array components;
} st_gamestate;

st_gamestate st_gamestate_init();
void         st_gamestate_cleanup(st_gamestate* gs);
st_entity    st_gamestate_new_entity();
int          st_entity_add_component(st_gamestate* gs,
				     st_entity e,
				     st_component_t type);
int          st_entity_has_component(st_gamestate* gs,
				     st_entity e,
				     st_component_t type);
void*        st_entity_get_component(st_gamestate* gs,
				     st_entity e,
				     st_component_t type);

#endif // ENTITY_H
