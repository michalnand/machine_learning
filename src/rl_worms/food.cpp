#include "food.h"

#include <math.h>
#include <math_.h>
#include <vpu.h>

Food::Food()
{
  count = 0;
  visualisation = nullptr;
}

Food::~Food()
{

}

void Food::init(unsigned int count, Visualisation *visualisation)
{
  this->count = count;
  this->visualisation = visualisation;
  this->food_size = 0.01;

  food.resize(count);
  create();
}

void Food::paint()
{
  float z = -3.0;

  for (unsigned int i = 0; i < food.size(); i++)
  if (food[i].active == true)
  {
    visualisation->paint_square(food[i].x,
                                 food[i].y,
                                 z,
                                 food_size,
                                 1.0,
                                 1.0,
                                 1.0);
  }
}

float Food::eat(float x, float y)
{
  float result = 0.0;

  for (unsigned int i = 0; i < food.size(); i++)
  if (food[i].active == true)
  {
    float dist = 0.0;
    dist+= (x - food[i].x)*(x - food[i].x);
    dist+= (y - food[i].y)*(y - food[i].y);
    dist = sqrt(dist);

    if (dist < food_size*2)
    {
      food[i].active = false;
      result = 1.0;
    }
  }

  unsigned int eaten = 0;
  for (unsigned int i = 0; i < food.size(); i++)
  if (food[i].active == false)
    eaten++;


  if (eaten > 0.75*food.size())
    create();

  return result;
}

std::vector<float> Food::state(float x, float y)
{
  unsigned int sensors_count = 8;

  std::vector<float> result;
  result.resize(sensors_count);

  float r = food_size*2.0;

  for (unsigned int i = 0; i < sensors_count; i++)
  {
    float theta = (3.141592654*i)/sensors_count;
    float x_pos = x + r*cos(theta);
    float y_pos = y + r*sin(theta);

    unsigned int idx = nearest_food(x_pos, y_pos);


    float distance = 0.0;
    distance+= (x_pos - food[idx].x)*(x_pos - food[idx].x);
    distance+= (y_pos - food[idx].y)*(y_pos - food[idx].y);

    result[i] = sqrt(distance);
  }

  vpu.normalise(&result[0], &result[0], -1.0, 1.0, result.size());


  return result;
}

void Food::create()
{
  float r = 0.2;
  float x_center = math.rnd();
  float y_center = math.rnd();

  for (unsigned int i = 0; i < food.size(); i++)
  {
    food[i].x = x_center + r*math.rnd();
    food[i].y = y_center + r*math.rnd();
    food[i].active = true;
  }
}

unsigned int Food::nearest_food(float x, float y)
{
  float dist_min = 1000000000.0;
  unsigned int result = 0;

  for (unsigned int i = 0; i < food.size(); i++)
  {
    float distance = 0.0;
    distance+= (food[i].x - x)*(food[i].x - x);
    distance+= (food[i].y - y)*(food[i].y - y);
    distance = sqrt(distance);

    if (distance < dist_min)
    {
      dist_min = distance;
      result = i;
    }
  }

  return result;
}
