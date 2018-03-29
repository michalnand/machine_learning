#ifndef _STACK_ITEM_H_
#define _STACK_ITEM_H_

#include <vector>

class StackItem
{
  public:
    std::vector<std::vector<float>> values;

    unsigned int area_width, area_height;
    unsigned int width, height;
    unsigned int x, y;
    unsigned int move_type;
    unsigned int state;

    int position, position_max, dimension_max;

  public:
    StackItem();

    StackItem(  unsigned int area_width, unsigned int area_height,
                unsigned int width, unsigned int height,
                unsigned int move_type);

    ~StackItem();

    void init(  unsigned int area_width, unsigned int area_height,
                unsigned int width, unsigned int height,
                unsigned int move_type);

    void process();

  protected:
    void set_position(unsigned int x, unsigned int y);
};


#endif
