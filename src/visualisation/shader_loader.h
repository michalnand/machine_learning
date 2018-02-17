#ifndef _SHADER_LOADER_H_
#define _SHADER_LOADER_H_

#include <stdio.h>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

/*
#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/glext.h>
*/

class ShaderLoader
{
  private:
    GLuint program_id;

  public:
    ShaderLoader();
    ShaderLoader(std::string vertex_file_name, std::string fragment_file_name);

    ~ShaderLoader();

    GLuint init(std::string vertex_file_name, std::string fragment_file_name);


    GLuint get_program();
    void run();
};

#endif
