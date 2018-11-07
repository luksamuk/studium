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
    TEST_TRANSFORM
} test_component_t;

typedef struct {
    st_vec3 position;
    st_mat4 model;
} test_transform_c;

static st_entity dummy;
static int count;

void
game_loop(st_gamestate* gs)
{
    count = (count + 1) % 360;
    if(st_entity_has_component(gs, dummy, TEST_TRANSFORM)) {
	test_transform_c* transform =
	    st_entity_get_component(gs, dummy, TEST_TRANSFORM);
	
	float angle_radians = st_degtorad(count);
	transform->position.x = 20.0f * sin(angle_radians);
	transform->position.y = 40.0f * cos(angle_radians);
	if(!(count % 20)) {
	    st_vec3_print(&transform->position);
	    printf("dt = %0.4lf\n", gs->delta_time);
	}
    }
}

int
main(void)
{
    st_log_info("Studium Engine v0.x");
    st_log_exec_debug(st_init());

    {
	st_mat4 transl = st_mat4_identity();
	st_mat4 scale  = st_mat4_identity();
	st_mat4 rotate = st_mat4_identity();

	st_translate3(&transl, (st_vec3){ 2.0f, 3.0f, 0.0f });
	st_scale2(&scale, (st_vec2) { 2.0f, 2.0f });
	st_rotate(&rotate, 2, st_degtorad(90.0f));

	st_mat4_print(&transl);
	
	// Test translation
	{
	    st_vec4 position = st_vec4_new((float[4]){5.0f, 1.0f, 0.0f, 1.0f});
	    st_vec4_print(&position);
	    st_vec4 new_pos  = st_matvec_mult4(&rotate, &position);
	    st_vec4_print(&new_pos);
	}
    }

    // Initialization
    st_window window = st_create_window(1280, 720, "Studium Engine");
    st_window_init_renderer(&window);

    // Prepare gamestate
    st_gamestate gs = st_gamestate_init();
    st_gamestate_register_component(&gs, TEST_TRANSFORM,
				    sizeof(test_transform_c));

    // Prepare dumb test
    count = 0;

    // Prepare dummy entity
    dummy = st_entity_new(&gs);
    st_entity_add_component(&gs, dummy, TEST_TRANSFORM);

    // Game loop
    st_window_game_loop(&window, game_loop, &gs);

    // Cleanup
    st_gamestate_cleanup(&gs);
    st_cleanup();
    return 0;
}
