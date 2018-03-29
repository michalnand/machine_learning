#ifndef _STACK_H_
#define _STACK_H_

#include "stack_item.h"

class Stack
{
  private:
    std::vector<StackItem*> items;
    StackItem current_item;

    unsigned int width, height;

  public:
    Stack(unsigned int width,
          unsigned int height);

    ~Stack();

    void action(unsigned int action_id);
    void main();

  private:
    void visualisation();
};

#endif
