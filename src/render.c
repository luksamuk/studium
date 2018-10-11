#include "studium/render.h"
#include "studium/macros.h"

#ifdef _WIN32
#    define APIENTRY __stdcall
#endif

#include "glad/glad.h"
#include "GLFW/glfw3.h"

void
st_window_init_renderer(const st_window* w)
{
    glfwMakeContextCurrent((GLFWwindow*)w->hnd);

    assert(gladLoadGLLoader((GLADloadproc) glfwGetProcAddress));
    
    glViewport(0, 0, w->width, w->height);
}

void
st_window_game_loop(const st_window* w,
		    void (*callback)())
{
    assert(callback);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    while(!glfwWindowShouldClose((GLFWwindow*)w->hnd)) {
	glfwPollEvents();

        (*callback)();

	glfwSwapBuffers((GLFWwindow*)w->hnd);
    }
}
