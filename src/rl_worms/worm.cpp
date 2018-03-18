#include "worm.h"
#include <math.h>
#include <math_.h>

Worm::Worm()
{
  this->x = 0.0;
  this->y = 0.0;
  this->length = 0;
  this->r = 0.0;
  this->g = 0.0;
  this->b = 0.0;
  this->visualisation = nullptr;

  left_speed = 0.0;
  right_speed = 0.0;
  inertia = 0.5;
  theta = 0.0;
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


void Worm::move(unsigned int action_id)
{
  float d_left = 0.0;
  float d_right = 0.0;
  float dt = 0.04;

  //compute motor forces
  switch (action_id)
  {
    case 0: d_left = 1.0; d_right = 1.0; break;
    case 1: d_left = 0.0; d_right = 1.0; break;
    case 2: d_left = 1.0; d_right = 0.0; break;
  }

  //force to speed
  left_speed = inertia*left_speed + (1.0 - inertia)*d_left;
  right_speed = inertia*right_speed + (1.0 - inertia)*d_right;


  //speed to position change in polar coordinates
  float d_dist  = dt*(left_speed + right_speed)/2.0;
  float d_theta = dt*(left_speed - right_speed)*16.0;


  theta+= d_theta;
  theta = fmod(theta, 2.0*PI);

  //polar coordinates to cartesian plague
  x+= d_dist*cos(theta);
  y+= d_dist*sin(theta);


  for (unsigned int i = 0; i < elements.size()-1; i++)
    elements[i] = elements[i+1];

  elements[elements.size()-1].x = x;
  elements[elements.size()-1].y = y;
}

void Worm::respawn()
{
  left_speed = 0.0;
  right_speed = 0.0;
  inertia = 0.5;
  theta = math.rnd()*2.0*PI;
  x = 0.0;
  y = 0.0;
}

void Worm::paint()
{
  float z = -3.0;
  float size = 0.03;
 
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
