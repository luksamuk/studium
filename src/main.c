#include <stdio.h>
#include "studium/core.h"
#include "studium/display.h"
#include "studium/render.h"
#include "studium/macros.h"

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
    
    // Alloc/dealloc test texture
    st_texture img;
    st_log_exec_debug(img = st_texture_load("res/box.png"));
    st_log_exec_debug(st_texture_unload(&img));

    // Print NULL vector; should provide an error
    st_vec2_print(NULL);

    // Vector arithmetic
    st_vec2 v1 = st_vec2_zero();
    st_vec2 v2 = st_vec2_one();
    st_vec2 v3 = st_vec2_new((float[2]){8.0f, 6.0f});
    st_vec3 v4 = st_vec3_new((float[3]){5.0f, 4.0f, 7.0f});

    /* Print vectors */
    
    fputs("v1 = ", stdout);
    st_vec2_print(&v1);

    fputs("v2 = ", stdout);
    st_vec2_print(&v2);

    fputs("v3 = ", stdout);
    st_vec2_print(&v3);

    fputs("v4 = ", stdout);
    st_vec3_print(&v4);

    // Attempt a vector sum and display
    {
	st_vec2 sum = st_vec2_sum(v2, v3);
	fputs("v2 + v3 = ", stdout);
	st_vec2_print(&sum);
    }
    
    // Print NULL matrix; should provide an error
    st_mat3_print(NULL);

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

    // Sum mat3 with its transpose
    {
	st_mat3 sum = st_mat3_sum(&m, &mt);
	fputs("m + m^t = ", stdout);
	st_mat3_print(&sum);
    }

    // Print mat4
    st_mat4 m2 = st_mat4_identity();
    fputs("m2 = ", stdout);
    st_mat4_print(&m2);

    // Scalar multiplication
    st_mat4 m3 = st_mat4_scalar_mult(3.0f, &m2);
    fputs("2 * m2 = ", stdout);
    st_mat4_print(&m3);

    // Game loop
    st_window_game_loop(&window, game_loop);

    // Cleanup
    st_log_exec_debug(st_cleanup());
    return 0;
}
