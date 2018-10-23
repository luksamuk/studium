#include <stdio.h>
#include "studium/core.h"
#include "studium/display.h"
#include "studium/render.h"
#include "studium/macros.h"
#include "studium/entity.h"

// https://github.com/Dav1dde/glad/blob/master/example/c%2B%2B/hellowindow2.cpp
// https://github.com/Dav1dde/glad

void
game_loop()
{
    
}

int
main(void)
{
    st_log_info("Studium Engine v0.x");
    st_log_exec_debug(st_init());

    // Initialization
    st_window window = st_create_window(1280, 720, "Studium Engine");
    st_window_init_renderer(&window);
    
    st_vec3 v4 = st_vec3_new((float[3]){5.0f, 4.0f, 7.0f});

    // Print mat2
    st_mat2 mat = st_mat2_identity();
    mat.a12 = 7.0f;
    mat.a21 = 9.0f;
    fputs("mat = ", stdout);
    st_mat2_print(&mat);

    // Print inverse of mat2
    {
	st_mat2 mat_inv;
	if(!st_mat2_inverse(&mat_inv, &mat)) {
	    fputs("mat^-1 = ", stdout);
	    st_mat2_print(&mat_inv);
	}
    }

    // Print mat3
    st_mat3 m = st_mat3_identity();
    m.a12 = 5.0f;
    m.a13 = 8.0f;
    fputs("m = ", stdout);
    st_mat3_print(&m);

    // Transpose mat3 and print
    st_mat3 mt = st_mat3_transpose(&m);
    fputs("m^t = ", stdout);
    st_mat3_print(&mt);

    // Fun with mat3 ops
    {
	// Sum mat3 with its transpose
	st_mat3 sum = st_mat3_sum(&m, &mt);
	fputs("m + m^t = ", stdout);
	st_mat3_print(&sum);

	// Print inverse of sum
	st_mat3 mat_inv;
	if(!st_mat3_inverse(&mat_inv, &sum)) {
	    fputs("(m + m^t)^-1 = ", stdout);
	    st_mat3_print(&mat_inv);
	}
    }

    // Print mat4
    st_mat4 m2 = st_mat4_identity();
    fputs("m2 = ", stdout);
    st_mat4_print(&m2);

    // Scalar multiplication
    st_mat4 m3 = st_mat4_scalar_mult(3.0f, &m2);
    fputs("2 * m2 = ", stdout);
    st_mat4_print(&m3);


    puts("Testing entities...");
    st_gamestate gs = st_gamestate_init();

    puts("Creating new entity");
    st_entity e = st_gamestate_new_entity(&gs);
    printf("Entity name? %zu\n"
	   "Entity has position? %d\n",
	   e,
	   st_entity_has_component(&gs, e, ST_POSITION));
    st_entity_add_component(&gs, e, ST_POSITION);
    printf("What about now? %d\n",
	   st_entity_has_component(&gs, e, ST_POSITION));


    puts("Creating new entity");
    st_entity e2 = st_gamestate_new_entity(&gs);
    printf("Entity name? %zu\n"
	   "Entity has position? %d\n",
	   e2,
	   st_entity_has_component(&gs, e2, ST_POSITION));
    st_entity_add_component(&gs, e2, ST_POSITION);
    printf("What about now? %d\n",
	   st_entity_has_component(&gs, e2, ST_POSITION));
    {
	st_pos_c* position = st_entity_get_component(&gs, e2, ST_POSITION);
	puts("e2's position:");
	st_vec3_print(&position->p);
	puts("All done.");
    }
    
    st_gamestate_cleanup(&gs);

    // Game loop
    st_window_game_loop(&window, game_loop);

    // Cleanup
    st_log_exec_debug(st_cleanup());
    return 0;
}
