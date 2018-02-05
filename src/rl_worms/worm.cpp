#include "worm.h"


Worm::Worm()
{
  this->x = 0.0;
  this->y = 0.0;
  this->length = 0;
  this->r = 0.0;
  this->g = 0.0;
  this->b = 0.0;
  this->visualisation = nullptr;
}

Worm::~Worm()
{

}

void Worm::init(float x, float y, unsigned int length,
                float r, float g, float b,
                Visualisation *visualisation)
{
  this->x = x;
  this->y = y;
  this->length = length;
  this->r = r;
  this->g = g;
  this->b = b;
  this->visualisation = visualisation;

  elements.resize(length);

  for (unsigned int i = 0; i < elements.size(); i++)
  {
    elements[i].x = x;
    elements[i].y = y;
  }
}


void Worm::move(float dx, float dy)
{
  x+= dx;
  y+= dy;

  for (unsigned int i = 0; i < elements.size()-1; i++)
    elements[i] = elements[i+1];
 
  elements[elements.size()-1].x = x;
  elements[elements.size()-1].y = y;
}

void Worm::paint()
{
  float z = -3.0;
  float size = 0.02;

  for (unsigned int i = 0; i < elements.size(); i++)
  {
    visualisation->paint_square( elements[i].x,
                                 elements[i].y,
                                 z,
                                 size,
                                 r,
                                 g,
                                 b);
  }
}
