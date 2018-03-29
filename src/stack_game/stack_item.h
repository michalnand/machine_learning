#ifndef _STACK_ITEM_H_
#define _STACK_ITEM_H_

#include <vector>

class StackItem
{
  public:
    std::vector<std::vector<float>> values;
    unsigned int x, y;
    unsigned int target_x, target_y;
    unsigned int width, height;

  protected:
    unsigned int area_width, area_height;

    unsigned int move_type;
    unsigned int state;

    int position, position_max, dimension_max;

  public:
    StackItem();

    StackItem(  unsigned int area_width, unsigned int area_height,
                unsigned int width, unsigned int height);

    StackItem(StackItem &other);

    ~StackItem();


    void process(bool move);
    void print();

    float compute_overlap(StackItem &other);

    void process_overlap(StackItem &other);

  protected:
    void set_position();
};


#endif
