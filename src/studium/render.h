#ifndef RENDER_H
#define RENDER_H

#include "core.h"
#include "stmath.h"

void st_window_init_renderer(const st_window* w);
void st_window_game_loop(const st_window* w,
			 void (*callback)());

typedef struct
{
    unsigned int id;
    int width;
    int height;
    int bpp;
} st_texture;

st_texture st_texture_load(const char* filename);
void       st_texture_unload(st_texture* img);
void       st_texture_render(st_texture* img,
			     st_vec2     pos);

#endif // RENDER_H
