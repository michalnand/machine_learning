#include "gl_polygon.h"



Polygon::Polygon()
{

}

Polygon::Polygon(float *vertex_buffer_data, float *color_buffer_data, unsigned int size)
{
  init(vertex_buffer_data, color_buffer_data, size);
}

Polygon::~Polygon()
{

}

float time = 0.0;

void Polygon::init(float *vertex_buffer_data, float *color_buffer_data, unsigned int size)
{
  this->size = size;
  this->triangles_count = size/3;

  // Generate 1 buffer, put the resulting identifier in vertexbuffer
  glGenBuffers(1, &vertexbuffer);

  // The following commands will talk about our 'vertexbuffer' buffer
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

  // Give our vertices to OpenGL.
  glBufferData(GL_ARRAY_BUFFER, size*sizeof(float), vertex_buffer_data, GL_STATIC_DRAW);


  this->color_buffer_data = color_buffer_data;
}

void Polygon::draw()
{
  //glPushMatrix();

  /*
  glRotatef(1.0, time, 0.0, 0.0);
  time+= 1.0;
  */

  glColor3f(1.0, 0.0, 0.0);


  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

  glVertexAttribPointer(
     0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
     triangles_count,                  // size
     GL_FLOAT,           // type
     GL_FALSE,           // normalized?
     0,                  // stride
     (void*)0            // array buffer offset
  );

  // glColorPointer(triangles_count, GL_FLOAT, 0, color_buffer_data);


  // Draw the triangle !
  glDrawArrays(GL_TRIANGLES, 0, triangles_count); // Starting from vertex 0; 3 vertices total -> 1 triangle
  glDisableVertexAttribArray(0);

//  glPopMatrix();
}
