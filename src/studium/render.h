#ifndef RENDER_H
#define RENDER_H

#include "display.h"
#include "stmath.h"
#include "entity.h"

// The following types are only defined to provide proper aliases
// and avoid confusion. But nothing stops the developer from using
// unsigned int if desired.
typedef unsigned  st_gpu_id;
typedef st_gpu_id st_gpu_buffer;
typedef st_gpu_id st_gpu_shader;
typedef st_gpu_id st_gpu_program;

typedef int       st_gpu_program_attrib;
typedef int       st_gpu_program_uniform;



/* Textures */

typedef struct
{
    st_gpu_id id;
    int       width;
    int       height;
    int       bpp;
} st_texture;

st_texture st_texture_load(const char* filename);
void       st_texture_unload(st_texture* img);
void       st_texture_render(st_texture* img,
                             st_vec2     pos);



/* Shaders */

typedef enum
{
    ST_SHADER_VERTEX,
    ST_SHADER_FRAGMENT
} st_shader_type;

st_gpu_shader st_shader_compile(st_shader_type type, const char* source);
st_gpu_shader st_shader_from_file(st_shader_type type, const char* filename);
void          st_shader_destroy(st_gpu_shader shader);



/* Programs (shader-related) */

st_gpu_program         st_program_link(st_gpu_shader* shaders, size_t count);
void                   st_program_destroy(st_gpu_program program);
void                   st_program_use(st_gpu_program program);
void                   st_program_bind_frag_data_location(st_gpu_program program,
                                                          st_gpu_id color_number,
                                                          const char* name);

// Attributes
st_gpu_program_attrib  st_program_attrib_location(st_gpu_program program,
                                                  const char* name);
void                   st_attrib_enable(st_gpu_program_attrib attrib);
void                   st_attrib_vertex_ptr_f(st_gpu_program_attrib attrib,
                                              size_t size,
                                              size_t stride,
                                              size_t offset);

// Uniforms
st_gpu_program_uniform st_program_uniform_location(st_gpu_program program,
                                                   const char* name);
void                   st_uniform_setf(st_gpu_program_uniform u,
                                       const float* values,
                                       size_t count);
void                   st_uniform_seti(st_gpu_program_uniform u,
                                       const int* values,
                                       size_t count);
void                   st_uniform_setu(st_gpu_program_uniform u,
                                       const unsigned* values,
                                       size_t count);
void                   st_uniform_set_mat2(st_gpu_program_uniform u,
                                           const st_mat2* m);
void                   st_uniform_set_mat3(st_gpu_program_uniform u,
                                           const st_mat3* m);
void                   st_uniform_set_mat4(st_gpu_program_uniform u,
                                           const st_mat4* m);



/* Defaults */

// Default shaders, precompiled on renderer startup
// TODO: Make those in a per-window fashion?
st_gpu_shader  st_shader_default_vs = 0;
st_gpu_shader  st_shader_default_fs = 0;
st_gpu_program st_program_default   = 0;



/* Renderer */
void st_window_init_renderer(const st_window* w);
void st_window_destroy_renderer(st_window* w);
void st_window_game_loop(st_window* w,
                         void (*callback)(st_gamestate*),
                         st_gamestate* gs);

#endif // RENDER_H
