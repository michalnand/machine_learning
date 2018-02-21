#include "tower.h"
#include <math.h>
#include <math_.h>

Tower::Tower()
{
  this->x = 0;
  this->y = 0;
  this->z = 0;

  this->range = 0;

  this->hit_probability = 0;
}

Tower::Tower(float x, float y, float z, float range, float life, float hit_probability)
{
  init(x, y, z, range, life, hit_probability);
}

Tower::~Tower()
{

}

void Tower::init(float x, float y, float z, float range, float life, float hit_probability)
{
  this->x = x;
  this->y = y;
  this->z = z;

  this->range = range;
  this->life  = life;

  this->hit_probability = hit_probability;
}

bool Tower::process(float x, float y, float z)
{
  if (hit(x, y, z) && (life > 0))
  {
    life--;
    return true;
  }

  return false;
}

bool Tower::alive()
{
  if (life > 0)
    return true;

  return false;
}

bool Tower::in_range(float x, float y, float z)
{
  float dist = 0.0;

  dist+= (this->x - x)*(this->x - x);
  dist+= (this->y - y)*(this->y - y);
  dist+= (this->z - z)*(this->z - z);

  dist = sqrt(dist);

  if (dist < range)
    return true;

  return false;
}

bool Tower::hit(float x, float y, float z)
{
  if (in_range(x, y, z))
  if (math.abs(math.rnd()) < hit_probability)
    return true;

  return false;
}
