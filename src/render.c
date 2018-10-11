#include "studium/render.h"
#include "studium/macros.h"

#ifdef _WIN32
#    define APIENTRY __stdcall
#endif

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#define STB_IMAGE_IMPLEMENTATION
#include "studium/stb_image.h"

void
st_window_init_renderer(const st_window* w)
{
    glfwMakeContextCurrent((GLFWwindow*)w->hnd);

    assert(gladLoadGLLoader((GLADloadproc) glfwGetProcAddress));
    
    glViewport(0, 0, w->width, w->height);
    glEnable(GL_TEXTURE_2D);
}

void
st_window_game_loop(const st_window* w,
		    void (*callback)())
{
    assert(callback);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    while(!glfwWindowShouldClose((GLFWwindow*)w->hnd)) {
	glfwPollEvents();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        (*callback)();

	glfwSwapBuffers((GLFWwindow*)w->hnd);
    }
}

st_texture
st_texture_load(const char* filename)
{
    st_texture img;
    unsigned char* data = stbi_load(filename,
				    &img.width,
				    &img.height,
				    &img.bpp,
				    0);
    
    assert(data);

    glGenTextures(1, &img.id);
    glBindTexture(GL_TEXTURE_2D, img.id);

    glTexParameterf(GL_TEXTURE_2D,
		    GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameterf(GL_TEXTURE_2D,
		    GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameterf(GL_TEXTURE_2D,
		    GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D,
		    GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glTexImage2D(GL_TEXTURE_2D,
		 0,
		 GL_RGBA8,
		 img.width,
		 img.height,
		 0,
		 GL_RGBA,
		 GL_UNSIGNED_BYTE,
		 data);

    glFinish();

    glGenerateMipmap(GL_TEXTURE_2D);
    st_log_exec_debug(stbi_image_free(data));

    return img;
}

void
st_texture_unload(st_texture* img)
{
    glDeleteTextures(1, &img->id);
    img->width = img->height = img->bpp = 0;
}
