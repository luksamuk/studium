#include "studium/entity.h"
#include "studium/macros.h"

/* ========================================================================== */
/*                                  st_gamestate                              */
/* ========================================================================== */

#define __st_add_component_array(components, instance, n)	\
    st_array_put(&components, n, (void*)&instance)

#define __st_add_new_component(components, size, c_type)		\
    {									\
        st_array component = st_array_new(size);			\
	st_array_put(&components, (size_t)c_type, (void*)&component);	\
    }



st_gamestate
st_gamestate_init()
{
    st_gamestate state;
    state.global_entity_count = 0;
    state.tags = st_array_new(sizeof(size_t));
    
    // "components" is an array of arrays
    state.components = st_array_new(sizeof(st_array));

    // Types of components must be added in the same order they
    // appear at st_component_t
    __st_add_new_component(state.components, sizeof(st_pos_c), ST_POSITION);
    __st_add_new_component(state.components, sizeof(st_mvp_c), ST_MVP);
    
    return state;
}

void
st_gamestate_cleanup(st_gamestate* gs)
{
    if(!gs) {
	st_log_err("attempt cleanup operation on NULL reference to gamestate");
	return;
    }
    size_t i;
    for(i = 0; i < gs->components.array_size; i++) {
	st_array* array = st_array_get(&gs->components, i);
	st_array_destroy(array);
    }
    st_array_destroy(&gs->components);
}


st_entity
st_gamestate_new_entity(st_gamestate* gs)
{
    size_t new_index = gs->global_entity_count;
    gs->global_entity_count++;
    return new_index;
}



/* ========================================================================== */
/*                                   st_entity                                */
/* ========================================================================== */

int
st_entity_add_component(st_gamestate* gs, st_entity e, st_component_t type)
{
    // Actually, there is no such thing as "ADDING" a component. The component
    // is always there for all entities, which make its access O(1).
    // What determines whether an entity has a component or not is a set
    // of bitwise flags.
    size_t* tags = st_array_get(&gs->tags, e);
    if(!tags) {
	st_log_err("unexisting entity");
	return 1;
    }
    
    *tags |= 1 << (size_t)type;
    return 0;
}

int
st_entity_has_component(st_gamestate* gs, st_entity e, st_component_t type)
{
    size_t* tags = st_array_get(&gs->tags, e);
    if(!tags) {
	st_log_err("unexisting entity");
	return 0;
    }
    return ((*tags) & (1 << (size_t) type)) != 0;
}

void*
st_entity_get_component(st_gamestate* gs, st_entity e, st_component_t type)
{
    st_array* component_array = (st_array*)st_array_get(&gs->components,
							(size_t)type);
    if(!component_array) {
	st_log_err("unexisting component type");
	return NULL;
    }
    
    return st_array_get(component_array, e);
}
