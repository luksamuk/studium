#include <stdio.h>
#include "studium/core.h"
#include "studium/display.h"
#include "studium/render.h"

//#define STUDIUM_RELEASE
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
    
    st_window window =
	st_create_window(1280, 720, "Studium Engine");
    st_window_init_renderer(&window);

    st_window_game_loop(&window, game_loop);
    
    st_cleanup();
    return 0;
}
