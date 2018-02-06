#ifndef _FOOD_H_
#define _FOOD_H_

#include <visualisation.h>
#include <vector>

struct sFoodElement
{
  float x, y;
  bool active;
};

class Food
{
  private:
    unsigned int count;
    Visualisation *visualisation;

    std::vector<sFoodElement> food;
    float food_size;

  public:
    Food();
    ~Food();

    void init(unsigned int count, Visualisation *visualisation);
    void paint();

    float eat(float x, float y);

    std::vector<float> state(float x, float y, float theta_ofs);

  private:
    void create();
    unsigned int nearest_food(float x, float y);

};

#endif
