#ifndef _WORM_H_
#define _WORM_H_

#include <visualisation.h>
#include <vector>

struct sWormElement
{
  float x, y;
};

class Worm
{
  public:
    float x, y;

  private:
    unsigned int length;
    float r, g, b;

    Visualisation *visualisation;

    std::vector<sWormElement> elements;

  public:
    Worm();
    ~Worm();

    void init(float x, float y, unsigned int length,
              float r, float g, float b,
              Visualisation *visualisation);

    void move(float dx, float dy);
    void paint();
};

#endif
