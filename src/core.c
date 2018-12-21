#include "studium/core.h"
#include "studium/macros.h"

#ifdef _WIN32
#    define APIENTRY __stdcall
#endif

#include "glad/glad.h"
#include "GLFW/glfw3.h"

int
st_init()
{
    if(!glfwInit()) {
        st_log_crit("cannot connect to window system");
        return 1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    return 0;
}


int
st_cleanup()
{
    glfwTerminate();
    return 0;
}
