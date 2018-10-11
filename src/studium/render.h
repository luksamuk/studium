#ifndef RENDER_H
#define RENDER_H

#include "core.h"

void st_window_init_renderer(const st_window* w);
void st_window_game_loop(const st_window* w,
			 void (*callback)());

#endif // RENDER_H
