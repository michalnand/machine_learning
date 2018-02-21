#ifndef _TOWER_H_
#define _TOWER_H_

class Tower
{
  private:
    float x, y, z;
    float range;
    float hit_probability;
    float life;

  public:

    Tower();
    Tower(float x, float y, float z, float range, float life, float hit_probability);
    ~Tower();

    void init(float x, float y, float z, float range, float life, float hit_probability);

    bool process(float x, float y, float z);
    bool alive();

  private:
    bool in_range(float x, float y, float z);
    bool hit(float x, float y, float z);
};

#endif
