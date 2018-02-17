#include "gl_window.h"



GLWindow::GLWindow()
{

}

GLWindow::GLWindow(std::string title, unsigned int width, unsigned int height)
{
  init(title, width, height);
} 

int GLWindow::init(std::string title, unsigned int width, unsigned int height)
{
  if( !glfwInit() )
    return -1;

  glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed

  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL
  //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

  // Open a window and create its OpenGL context
  window = glfwCreateWindow( width, height, title.c_str(), NULL, NULL);
  if( window == NULL )
  {
      glfwTerminate();
      return -2;
  }

  glfwMakeContextCurrent(window); // Initialize GLEW

  glewExperimental = true; // Needed in core profile
  if (glewInit() != GLEW_OK)
  {
      return -3;
  }

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);



  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);

  glShadeModel(GL_SMOOTH);
  	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  	glEnable(GL_COLOR_MATERIAL);



  return 0;
}

void GLWindow::draw_callback()
{

}

void GLWindow::main()
{
  draw_callback();

  glfwSwapBuffers(window);
  glfwPollEvents();
}

bool GLWindow::end()
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE ) == GLFW_PRESS)
    return true;

  if (glfwWindowShouldClose(window) != 0)
    return true;

  return false;
}

GLFWwindow* GLWindow::get_window()
{
  return window;
}
