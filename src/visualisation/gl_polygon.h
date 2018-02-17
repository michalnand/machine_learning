#ifndef _POLYGON_H_
#define _POLYGON_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>

class Polygon
{
  private:
    GLuint vertexbuffer;
    unsigned int size, triangles_count;

    float *color_buffer_data;
    
  public:
    Polygon();
    Polygon(float *vertex_buffer_data, float *color_buffer_data, unsigned int size);
    ~Polygon();

    void init(float *vertex_buffer_data, float *color_buffer_data, unsigned int size);
    void draw();
};

#endif
