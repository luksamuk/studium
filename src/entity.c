#include "studium/entity.h"
#include "studium/macros.h"

/* ========================================================================== */
/*                                  st_gamestate                              */
/* ========================================================================== */

#define __st_add_component_array(components, instance, n)       \
    st_array_put(&components, n, (void*)&instance)

#define __st_add_new_component(components, size, c_type)                \
    {                                                                   \
        st_array component = st_array_new(size);                        \
        st_array_put(&components, (size_t)c_type, (void*)&component);   \
    }



st_gamestate
st_gamestate_init()
{
    st_gamestate state;
    state.global_entity_count    = 1;
    state.global_component_count = 0;
    state.tags = st_array_new(sizeof(size_t));
    state.tags = st_array_new(sizeof(int));
    
    // "components" is an array of arrays
    state.components = st_array_new(sizeof(st_array));
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
    st_array_destroy(&gs->tags);
    st_array_destroy(&gs->dead);
    gs->global_component_count = 0;
    gs->global_entity_count = 1;
    gs->delta_time = 0;
}

int
st_gamestate_register_component(st_gamestate* gs, size_t identifier,
                                size_t byte_size)
{
    if(!gs) {
        st_log_err("attempt operation on NULL reference to gamestate");
        return 1;
    }
    
    __st_add_new_component(gs->components, byte_size, identifier);
    return 0;
}



/* ========================================================================== */
/*                                   st_entity                                */
/* ========================================================================== */

st_entity
st_entity_new(st_gamestate* gs)
{
    if(!gs) {
        st_log_err("attempt operation on NULL reference to gamestate");
        return 0;
    }
    size_t new_index = gs->global_entity_count;
    gs->global_entity_count++;
    return new_index;
}

int
st_entity_add_component(st_gamestate* gs, st_entity e, st_component_t type)
{
    // Actually, there is no such thing as "ADDING" a component. The component
    // is always there for all entities, which make its access O(1).
    // What determines whether an entity has a component or not is a set
    // of bitwise flags.
    size_t* tags = st_array_get(&gs->tags, e - 1);
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
    size_t* tags = st_array_get(&gs->tags, e - 1);
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
    
    return st_array_get(component_array, e - 1);
}

int
st_entity_alive(st_gamestate* gs, st_entity e)
{
    int* dead = st_array_get(&gs->dead, e - 1);
    if(!dead) {
        st_log_err("unexisting entity");
        return 0;
    }
    return !(*dead);
}

int
st_entity_kill(st_gamestate* gs, st_entity* e)
{
    int* dead = st_array_get(&gs->dead, (*e) - 1);
    if(!dead) {
        st_log_err("unexisting entity");
        return 1;
    }
    *dead = 1;
    *e = 0;
    return 0;
}
