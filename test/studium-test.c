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
    TEST_TRANSFORM,
    TEST_COORDINATE,
    TEST_RENDERER
} test_component_t;

typedef struct {
    st_vec4 position;
} test_coordinate_c;

typedef struct {
    st_mat4 translation;
    st_mat4 scale;
    st_mat4 rotation;
} test_transform_c;

typedef struct {
    st_texture texture;
    st_mat4    vp;
} test_renderer_c;

static st_entity dummy;
static int count;

void
init_player(st_gamestate* gs, st_entity e)
{
    st_entity_add_component(gs, dummy, TEST_TRANSFORM);
    st_entity_add_component(gs, dummy, TEST_COORDINATE);
    st_entity_add_component(gs, dummy, TEST_RENDERER);

    // No need for checking. Retrieve transform component
    // already, then do stuff
    test_transform_c* transform =
	st_entity_get_component(gs, e, TEST_TRANSFORM);

    test_coordinate_c* coord =
	st_entity_get_component(gs, e, TEST_COORDINATE);

    test_renderer_c* rend =
	st_entity_get_component(gs, e, TEST_RENDERER);
	
    coord->position        = st_vec4_origin();
    transform->translation = st_mat4_identity();
    transform->scale       = st_mat4_identity();
    transform->rotation    = st_mat4_identity();

    // Initialize rendering stuff
    rend->texture = st_texture_load("res/box.png");

    st_program_use(st_program_default);

    st_gpu_program_attrib attr_pos =
	st_program_attrib_location(st_program_default, "position"),
	attr_col = st_program_attrib_location(st_program_default, "color"),
	attr_tex = st_program_attrib_location(st_program_default, "texcoord");

    st_gpu_program_uniform uni_mvp =
	st_program_uniform_location(st_program_default, "mvp");
	
}

void
update_player(st_gamestate* gs, st_entity e)
{
    if(st_entity_has_component(gs, e, TEST_TRANSFORM)
       && st_entity_has_component(gs, e, TEST_COORDINATE)) {
	test_transform_c* transform =
	    st_entity_get_component(gs, dummy, TEST_TRANSFORM);
	test_coordinate_c* coord =
	    st_entity_get_component(gs, e, TEST_COORDINATE);

	// Rotate our sad friend
	float angle_radians = st_degtorad(count);
	transform->rotation = st_mat4_identity();
	st_rotate(&transform->rotation, 2, angle_radians * gs->delta_time);

	// Transform our sad friend's position
	transform->translation = st_mat4_identity();
	st_translate2(&transform->translation,
		      (st_vec2){ 20.0f * sin(angle_radians) * gs->delta_time,
				 40.0f * cos(angle_radians) * gs->delta_time });

	// Apply transform accordingly
	coord->position = st_matvec_mult4(&transform->translation,
					  &coord->position);

	// Print stuff
	if(!(count % 200)) {
	    st_log_info_f("position: ");
	    st_vec4_print(&coord->position);
	    /* st_log_info_f("translation: "); */
	    /* st_mat4_print(&transform->translation); */
	    st_log_info_f("dt = %0.4lf\n", gs->delta_time);
	}
    }
}


void
game_init(st_gamestate* gs)
{
    // Prepare some components
    st_gamestate_register_component(gs, TEST_TRANSFORM, sizeof(test_transform_c));
    st_gamestate_register_component(gs, TEST_COORDINATE, sizeof(test_coordinate_c));
    st_gamestate_register_component(gs, TEST_RENDERER, sizeof(test_renderer_c));
    
    // Prepare dumb test
    count = 0;

    // Prepare dummy entity
    dummy = st_entity_new(gs);
    init_player(gs, dummy);
}

void
game_loop(st_gamestate* gs)
{
    count = (count + 1) % 360;
    update_player(gs, dummy);
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

    // Initialize stuff
    game_init(&gs);

    st_log_exec_debug(
	st_gpu_shader vs = st_shader_from_file(ST_SHADER_VERTEX,
					       "res/shaders/default.vs.glsl");
	st_gpu_shader fs = st_shader_from_file(ST_SHADER_FRAGMENT,
					       "res/shaders/default.fs.glsl");
	);
    
    // Game loop
    st_window_game_loop(&window, game_loop, &gs);

    // Cleanup
    st_gamestate_cleanup(&gs);
    st_window_destroy_renderer(&window);
    st_cleanup();
    return 0;
}
