#include "stack_item.h"

StackItem::StackItem()
{

}

StackItem::StackItem(   unsigned int area_width, unsigned int area_height,
                        unsigned int width, unsigned int height,
                        unsigned int move_type)
{
  init(area_width, area_height,
       width, height,
       move_type);
}

StackItem::~StackItem()
{

}

void StackItem::init( unsigned int area_width, unsigned int area_height,
                      unsigned int width, unsigned int height,
                      unsigned int move_type)
{
  this->area_width = area_width;
  this->area_height = area_height;
  this->width = width;
  this->height = height;
  this->x = 0;
  this->y = 0;
  this->move_type = move_type;

  state = 0;
  position = 0;

  if ((move_type%2) == 0)
  {
    this->x = (area_width - width)/2;
    this->y = 0;
    dimension_max = width;
    position_max = area_width;
  }
  else
  {
    this->x = 0;
    this->y = (area_height - height)/2;
    dimension_max = height;
    position_max = area_height;
  }

  values.resize(area_height);
  for (unsigned int j = 0; j < values.size(); j++)
  {
    values[j].resize(area_width);
    for (unsigned int i = 0; i < values[j].size(); i++)
      values[j][i] = 0.0;
  }

  set_position(0, 0);
}

void StackItem::set_position(unsigned int x, unsigned int y)
{
  for (unsigned int j = 0; j < values.size(); j++)
    for (unsigned int i = 0; i < values[j].size(); i++)
      values[j][i] = 0.0;

  for (unsigned int j = 0; j < height; j++)
    for (unsigned int i = 0; i < width; i++)
      if ( (j + y) < values.size() && (i + x) < values[j].size() )
        values[j + y][i + x] = 1.0;
}


void StackItem::process()
{
  switch (state)
  {
    case 0:
            position++;
            if (position >= (position_max - dimension_max))
              state = 1;
            break;

    case 1:
            position--;
            if (position <= dimension_max)
              state = 0;
            break;

    case 2:
            break;
  }
}
