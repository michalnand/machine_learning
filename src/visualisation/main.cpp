#include <stdio.h>

#include <gl_window.h>
#include <gl_polygon.h>
#include <shader_loader.h>

#include <math_.h>
#include <timer.h>

#include <GL/glut.h>
#include <GL/glew.h>

float triangle_vertex[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};

float triangle_color[] = {
   1.0f,  0.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
   0.0f,  0.0f, 1.0f,
};


int main()
{
  math.srand(time(NULL));

  GLWindow window;
  int window_res = window.init("visualisation", 400, 400);
  printf("windonw init res %i\n", window_res);

  Polygon triangle(triangle_vertex, triangle_color, 3*3);
 
  ShaderLoader my_shader;
  int res = my_shader.init("shader/my_shader.vs", "shader/my_shader.fs");
  printf("shader init result %i\n", res);

  while (!window.end())
  {
    glClearColor(0.0, 0.0, 0.3, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    triangle.draw();

    window.main();
  }

  printf("program done\n");

  return 0;
}
