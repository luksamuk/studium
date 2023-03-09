#include "studium/core.h"
#include "studium/display.h"
#include "studium/macros.h"

#ifdef _WIN32
#    define APIENTRY __stdcall
#endif

#include "glad/glad.h"
#include "GLFW/glfw3.h"

st_window
st_create_window(int width, int height, const char* title)
{
    st_window w;

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    
    w.hnd = (void*)glfwCreateWindow(width, height, title, NULL, NULL);
    
    if(!w.hnd) {
        st_log_crit("cannot create window");
        return (st_window){ 0 };
    }
    
    w.width = width;
    w.height = height;
    w.last_time = glfwGetTime();
    return w;
}
