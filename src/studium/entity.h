#ifndef ENTITY_H
#define ENTITY_H

#include "array.h"
#include "stmath.h"


typedef size_t st_component_t;


// Structure of Arrays approach
typedef struct {
    size_t   global_entity_count;
    size_t   global_component_count;
    st_array tags;
    st_array dead;
    st_array components;
    double   delta_time;
} st_gamestate;


typedef size_t st_entity;


st_gamestate st_gamestate_init();
void         st_gamestate_cleanup(st_gamestate* gs);
int          st_gamestate_register_component(st_gamestate* gs,
					     size_t identifier,
					     size_t byte_size);

st_entity    st_entity_new(st_gamestate* gs);
int          st_entity_add_component(st_gamestate* gs,
				     st_entity e,
				     st_component_t type);
int          st_entity_has_component(st_gamestate* gs,
				     st_entity e,
				     st_component_t type);
void*        st_entity_get_component(st_gamestate* gs,
				     st_entity e,
				     st_component_t type);
int          st_entity_alive(st_gamestate* gs, st_entity e);
int          st_entity_kill(st_gamestate* gs, st_entity* e);

#endif // ENTITY_H
