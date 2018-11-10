#include "studium/render.h"
#include "studium/macros.h"

#ifdef _WIN32
#    define APIENTRY __stdcall
#endif

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#define STB_IMAGE_IMPLEMENTATION
#include "studium/stb_image.h"


/* ========================================================================== */
/*                                 Textures                                   */
/* ========================================================================== */

st_texture
st_texture_load(const char* filename)
{
    st_texture img;
    unsigned char* data = stbi_load(filename,
				    &img.width,
				    &img.height,
				    &img.bpp,
				    0);

    if(!data) {
	st_log_err("could not load texture");
	return (st_texture){ 0 };
    }

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
    if(!img) {
	st_log_err("attempt on unloading an invalid reference to a texture");
	return;
    }

    img->width = img->height = img->bpp = 0;

    if(!img->id) {
	st_log_warn("texture does not have a valid id, skipping");
	return;
    }
    
    glDeleteTextures(1, &img->id);
    img->id = 0;
}

/* ========================================================================== */
/*                                  Shaders                                   */
/* ========================================================================== */

/* Default shaders for general purpose */
static const char* st_shadersrc_default_vs_gl =
"#version 150 core\n"
"\n"
"// Expected\n"
"in vec4 position;\n"
"in vec4 color;\n"
"in vec2 texcoord;\n"
"\n"
"// Out to next pass\n"
"out vec4 Color;\n"
"out vec2 Texcoord;\n"
"\n"
"uniform mat4 mvp;\n"
"\n"
"void main()\n"
"{\n"
"    // Pass along color and texcoord\n"
"    Color    = color;\n"
"    Texcoord = texcoord;\n"
"    // Calculate position\n"
"    gl_Position = mvp * position;\n"
"}\n";

static const char* st_shadersrc_default_fs_gl =
"#version 150 core\n"
"\n"
"// Inherit from last pass\n"
"in vec4 Color;\n"
"in vec2 Texcoord;\n"
"\n"
"out vec4 outColor;\n"
"\n"
"// Texture sampler as uniform\n"
"uniform sampler2D tex;\n"
"\n"
"void main()\n"
"{\n"
"    // Performs a very simple blending operation\n"
"    vec4 texColor = texture(tex, Texcoord);\n"
"    outColor      = texColor * Color;\n"
"}\n";


st_gpu_shader
st_shader_compile(st_shader_type type, const char* source)
{
    if(!source) {
	st_log_err("NULL reference to source code");
	return 0;
    }
    
    // OpenGL shader type conversion.
    // I am assuming shader type definitions are not sequential.
    GLenum shader_type;
    switch(type) {
    case ST_SHADER_VERTEX:   shader_type = GL_VERTEX_SHADER;   break;
    case ST_SHADER_FRAGMENT: shader_type = GL_FRAGMENT_SHADER; break;
    default: break; // Enum usage prevents problems, though.
    };

    st_gpu_shader shader = glCreateShader(shader_type);
    if(!shader) {
	st_log_err("cannot create shader");
	return 0;
    }

    // Set shader source and compile
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    // Check status, report errors
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if(status != GL_TRUE) {
	char buffer[512];
	glGetShaderInfoLog(shader, 512, NULL, buffer);
	st_log_err_f("%s\n", buffer);
	// Delete the shader, as we will not need it anymore
	glDeleteShader(shader);
	return 0;
    }

    st_log_info("shader compilation successful");
    return shader;
}

void st_shader_destroy(st_gpu_shader shader)
{
    glDeleteShader(shader);
}



/* ========================================================================== */
/*                                  Program                                   */
/* ========================================================================== */

st_gpu_program
st_program_link(st_gpu_shader* shaders, size_t count)
{
    if(!shaders || !count) {
	st_log_err("NULL reference or number of shaders");
	return 0;
    }
    
    st_gpu_program program = glCreateProgram();
    if(!program) {
	st_log_err("cannot create program");
	return 0;
    }

    // Attach each shader
    {
	int i;
	for(i = 0; i < count; i++)
	    glAttachShader(program, shaders[i]);
    }

    glLinkProgram(program);

    // Check status, report errors
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if(status != GL_TRUE) {
	char buffer[512];
	glGetProgramInfoLog(program, 512, NULL, buffer);
	st_log_err_f("error linking program: %s\n", buffer);
	// Delete program, as we will not need it anymore
	glDeleteProgram(program);
	return 0;
    }

    st_log_info("program linking successful");
    return program;
}

void
st_program_destroy(st_gpu_program program)
{
    glDeleteProgram(program);
}

void
st_program_use(st_gpu_program program)
{
    glUseProgram(program);
}

void
st_program_bind_frag_data_location(st_gpu_program program,
				   st_gpu_id color_number,
				   const char* name)
{
    if(!name) {
	st_log_err("NULL reference to fragment data location name");
	return;
    }
    glBindFragDataLocation(program, color_number, name);
}


/* -------------------------------------------------------------------------- */
/*                                  Attributes                                */
/* -------------------------------------------------------------------------- */

st_gpu_program_attrib
st_program_attrib_location(st_gpu_program program, const char* name)
{
    if(!name) {
	st_log_err("NULL reference to attribute name");
	return -1;
    }
    
    int attrib = glGetAttribLocation(program, name);
    if(attrib == -1)
	st_log_err_f("cannot get location of attribute \"%s\"\n", name);
    
    return attrib;
}

void
st_attrib_enable(st_gpu_program_attrib attrib)
{
    glEnableVertexAttribArray(attrib);
}

void
st_attrib_vertex_ptr_f(st_gpu_program_attrib attrib,
		       size_t size,
		       size_t stride,
		       size_t offset)
{
    if(!offset) {
	st_log_err("NULL reference to attribute offset");
	return;
    }
    glVertexAttribPointer(attrib, size, GL_FLOAT, GL_FALSE,
			  stride * sizeof(float),
			  (void*)(offset * sizeof(float)));
}

/* -------------------------------------------------------------------------- */
/*                                  Uniforms                                  */
/* -------------------------------------------------------------------------- */

st_gpu_program_uniform
st_program_uniform_location(st_gpu_program program, const char* name)
{
    if(!name) {
	st_log_err("NULL reference to uniform name");
	return -1;
    }

    int uniform = glGetUniformLocation(program, name);
    if(uniform == -1)
	st_log_err_f("cannot get location of uniform \"%s\"\n", name);

    return uniform;
}

void
st_uniform_setf(st_gpu_program_uniform u, const float* values, size_t count)
{
    if(!values) {
	st_log_err("NULL reference to new uniform values");
	return;
    }
    glUniform1fv(u, count, values);
}

void
st_uniform_seti(st_gpu_program_uniform u, const int* values, size_t count)
{
    if(!values) {
	st_log_err("NULL reference to new uniform values");
	return;
    }
    glUniform1iv(u, count, values);
}

void
st_uniform_setu(st_gpu_program_uniform u, const unsigned* values, size_t count)
{
    if(!values) {
	st_log_err("NULL reference to new uniform values");
	return;
    }
    glUniform1uiv(u, count, values);
}

void
st_uniform_set_mat2(st_gpu_program_uniform u, const st_mat2* m)
{
    if(!m) {
	st_log_err("NULL reference to new matrix uniform value");
	return;
    }
    glUniformMatrix2fv(u, 1, 0, m->A);
}

void
st_uniform_set_mat3(st_gpu_program_uniform u, const st_mat3* m)
{
    if(!m) {
	st_log_err("NULL reference to new matrix uniform value");
	return;
    }
    glUniformMatrix3fv(u, 1, 0, m->A);
}

void
st_uniform_set_mat4(st_gpu_program_uniform u, const st_mat4* m)
{
    if(!m) {
	st_log_err("NULL reference to new matrix uniform value");
	return;
    }
    glUniformMatrix4fv(u, 1, 0, m->A);
}

/* ========================================================================== */
/*                                  Renderer                                  */
/* ========================================================================== */

static inline int
__st_check_window(const st_window* w)
{
    if(!w) {
	st_log_crit("invalid reference to st_window");
	return 1;
    } else if(!w->hnd) {
	st_log_crit("window was not created");
	return 1;
    }
    return 0;
}

static void
__st_gl_debug_callback(GLenum source,
		       GLenum type,
		       GLuint id,
		       GLenum severity,
		       GLsizei length,
		       const GLchar* msg,
		       const void* user_param)
{
    const char* s_src, *s_type;
    
    switch(source) {
    case 0x8246: s_src = "API";             break;
    case 0x8247: s_src = "Window System";   break;
    case 0x8248: s_src = "Shader Compiler"; break;
    case 0x8249: s_src = "Third Party";     break;
    case 0x824A: s_src = "Application";     break;
    case 0x824B: s_src = "Other";           break;
    default:     s_src = "Unknown";         break;
    }

    switch(type) {
    case 0x824C: s_type = "Error";                break;
    case 0x824D: s_type = "Deprecated Behaviour"; break;
    case 0x824E: s_type = "Undefined Behaviour";  break;
    case 0x824F: s_type = "Portability";          break;
    case 0x8250: s_type = "Performance";          break;
    case 0x8251: s_type = "Other";                break;
    default:     s_type = "Unknown";              break;
    }

    switch(severity) {
    case 0x9146:
	st_log_err_f("GL %s %s: %s\n", s_src, s_type, msg);
	break;
    case 0x9147:
	st_log_warn_f("GL %s %s: %s\n", s_src, s_type, msg);
	break;
    case 0x9148:
    default:
	st_log_info_f("GL %s %s: %s\n", s_src, s_type, msg);
	break;
    }
}

void
st_window_init_renderer(const st_window* w)
{
    if(!__st_check_window(w)) {
	glfwMakeContextCurrent((GLFWwindow*)w->hnd);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
	    st_log_crit("cannot initialize GLAD");
	    return;
	}

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(__st_gl_debug_callback, NULL);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL,
			      GL_TRUE);
	
	glViewport(0, 0, w->width, w->height);

	// Prepare shaders
	st_shader_default_vs =
	    st_shader_compile(ST_SHADER_VERTEX, st_shadersrc_default_vs_gl);
	st_shader_default_fs =
	    st_shader_compile(ST_SHADER_FRAGMENT, st_shadersrc_default_fs_gl);
	
	st_gpu_shader shaders[] = {
	    st_shader_default_vs, st_shader_default_fs
	};
	
	st_program_default = st_program_link(shaders, 2);
	st_program_bind_frag_data_location(st_program_default, 0, "outColor");
	st_program_use(st_program_default);
    }
}

void
st_window_destroy_renderer(st_window* w)
{
    st_shader_destroy(st_shader_default_vs);
    st_shader_destroy(st_shader_default_fs);
    st_program_destroy(st_program_default);
}

void
st_window_game_loop(st_window* w,
		    void (*callback)(st_gamestate*),
		    st_gamestate* gs)
{
    if(!__st_check_window(w)) {
	if(!callback) {
	    st_log_err("invalid game loop callback");
	    return;
	}
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	while(!glfwWindowShouldClose((GLFWwindow*)w->hnd)) {
	    // Dispatch events, clear screen
	    glfwPollEvents();
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	    // Delta time calculation
	    double new_time = glfwGetTime();
	    gs->delta_time = new_time - w->last_time;
	    w->last_time = new_time;

	    // Call gameloop function callback
	    (*callback)(gs);

	    // Swap buffers
	    glfwSwapBuffers((GLFWwindow*)w->hnd);
	}
    }
}
