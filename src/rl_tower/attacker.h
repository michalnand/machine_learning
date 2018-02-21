#ifndef _ATTACKER_H_
#define _ATTACKER_H_

#include "tower.h"

class Attacker
{
  private:
    float x, y, z;

  public:
    Attacker();
    ~Attacker();

    void init(float x, float y, float z);

    void process(std::vector<class Tower*> &towers);
};

#endif
