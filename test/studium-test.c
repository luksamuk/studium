#include <stdio.h>
#include "studium/core.h"
#include "studium/display.h"
#include "studium/render.h"
#include "studium/macros.h"
#include "studium/entity.h"

// https://github.com/Dav1dde/glad/blob/master/example/c%2B%2B/hellowindow2.cpp
// https://github.com/Dav1dde/glad


// Dummy components.
typedef enum {
    TEST_POSITION,
    TEST_MVP
} test_component_t;

typedef struct {
    st_vec3 p;
} test_pos_c;

typedef struct {
    st_mat4 model;
    st_mat4 view;
    st_mat4 projection;
} test_mvp_c;

static st_entity dummy;
static int count;

void
game_loop(st_gamestate* gs)
{
    count = (count + 1) % 360;
    if(st_entity_has_component(gs, dummy, TEST_POSITION)) {
	test_pos_c* position =
	    st_entity_get_component(gs, dummy, TEST_POSITION);
	
	float angle_radians = st_degtorad(count);
	position->p.x = 20.0f * sin(angle_radians);
	position->p.y = 40.0f * cos(angle_radians);
	if(!(count % 20)) {
	    st_vec3_print(&position->p);
	}
    }
}

int
main(void)
{
    st_log_info("Studium Engine v0.x");
    st_log_exec_debug(st_init());

    // Initialization
    st_window window = st_create_window(1280, 720, "Studium Engine");
    st_window_init_renderer(&window);

    // Prepare gamestate
    st_gamestate gs = st_gamestate_init();
    st_gamestate_register_component(&gs, TEST_POSITION, sizeof(test_pos_c));
    st_gamestate_register_component(&gs, TEST_MVP,      sizeof(test_mvp_c));

    // Prepare dumb test
    count = 0;

    // Prepare dummy entity
    dummy = st_gamestate_new_entity(&gs);
    st_entity_add_component(&gs, dummy, TEST_POSITION);

    // Game loop
    st_window_game_loop(&window, game_loop, &gs);

    // Cleanup
    st_gamestate_cleanup(&gs);
    st_cleanup();
    return 0;
}
