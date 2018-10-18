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
    w.hnd = (void*)glfwCreateWindow(width, height, title, NULL, NULL);
    
    if(!w.hnd) {
	st_log_crit("cannot create window");
	return (st_window){ 0 };
    }
    
    w.width = width;
    w.height = height;
    return w;
}
