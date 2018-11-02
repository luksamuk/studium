#ifndef RENDER_H
#define RENDER_H

#include "display.h"
#include "entity.h"

void st_window_init_renderer(const st_window* w);
void st_window_game_loop(st_window* w,
			 void (*callback)(st_gamestate*),
			 st_gamestate* gs);

typedef struct
{
    unsigned int id;
    int width;
    int height;
    int bpp;
} st_texture;

st_texture st_texture_load(const char* filename);
void       st_texture_unload(st_texture* img);
//void       st_texture_render(st_texture* img, float x, float y);

#endif // RENDER_H
