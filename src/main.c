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
    
    st_window window = st_create_window(1280, 720, "Studium Engine");
    
    st_window_init_renderer(&window);

    st_texture img;
    st_log_exec_debug(img = st_texture_load("res/box.png"));
    st_log_exec_debug(st_texture_unload(&img));

    st_mat3_print(NULL);
    
    st_mat3 m = st_mat3_identity();
    m.a12 = 5.0f; m.a13 = 8.0f;
    fputs(" m = ", stdout);
    st_mat3_print(&m);
    
    st_mat3 mt = st_mat3_transpose(&m);
    fputs(" m^t = ", stdout);
    st_mat3_print(&mt);

    st_mat4 m2 = st_mat4_identity();
    fputs(" m2 = ", stdout);
    st_mat4_print(&m2);
    
    st_window_game_loop(&window, game_loop);
    
    st_log_exec_debug(st_cleanup());
    return 0;
}
