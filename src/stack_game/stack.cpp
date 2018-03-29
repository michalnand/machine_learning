#include "stack.h"



Stack::Stack(unsigned int width,
             unsigned int height)
{
  this->width  = width;
  this->height = height;

  for (unsigned int i = 0; i < 16; i++)
  {
    unsigned int item_width  = 0.75*(math.rand()%width);
    unsigned int item_height = 0.75*(math.rand()%height);
    items.push_back(new StackItem(width, height, item_width, item_height))
  }
}

Stack::~Stack()
{

}

void Stack::action(unsigned int action_id)
{

}


void Stack::visualisation()
{

}
