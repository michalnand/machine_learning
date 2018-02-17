#ifndef _GL_WINDOW_H_
#define _GL_WINDOW_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>

#include <string>
#include <vector>

class GLWindow
{
  private:
    GLFWwindow* window;

  public:
    GLWindow();
    GLWindow(std::string title, unsigned int width = 256, unsigned int height = 256);

    int init(std::string title, unsigned int width = 256, unsigned int height = 256);

    virtual void draw_callback();

    void main();

    bool end();

    GLFWwindow* get_window();
};

#endif
