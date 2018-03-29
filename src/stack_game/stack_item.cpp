#include "stack_item.h"

#include <stdio.h>
#include <math_.h>

StackItem::StackItem()
{

}

StackItem::StackItem(   unsigned int area_width, unsigned int area_height,
                        unsigned int width, unsigned int height)
{
  this->area_width = area_width;
  this->area_height = area_height;
  this->width = width;
  this->height = height;

  this->x = (area_width - width)/2;
  this->y = (area_height - height)/2;

  target_x = this->x;
  target_y = this->y;


  this->move_type = 0;

  state = 2;
  position = 0;


  values.resize(area_height);
  for (unsigned int j = 0; j < values.size(); j++)
  {
    values[j].resize(area_width);
    for (unsigned int i = 0; i < values[j].size(); i++)
      values[j][i] = 0.0;
  }

  set_position();
}


StackItem::StackItem(StackItem &other)
{
  this->area_width = other.area_width;
  this->area_height = other.area_height;
  this->width = other.width;
  this->height = other.height;

  this->move_type = other.move_type+1;

  target_x = other.x;
  target_y = other.y;

  state = 0;
  position = 0;

  if ((move_type%2) == 0)
  {
    this->x = (other.area_width - other.width)/2;
    this->y = 0;
    dimension_max = height;
    position_max  = area_height;
    position = math.rand()%(other.area_height - other.height);
  }
  else
  {
    this->x = 0;
    this->y = (other.area_height - other.height)/2;
    dimension_max = width;
    position_max  = area_width;
    position = math.rand()%(other.area_width - other.width);
  }

  values.resize(area_height);
  for (unsigned int j = 0; j < values.size(); j++)
  {
    values[j].resize(area_width);
    for (unsigned int i = 0; i < values[j].size(); i++)
      values[j][i] = 0.0;
  }

  set_position();
}

StackItem::~StackItem()
{

}

void StackItem::set_position()
{
  for (unsigned int j = 0; j < values.size(); j++)
    for (unsigned int i = 0; i < values[j].size(); i++)
      values[j][i] = 0.0;

  for (unsigned int j = 0; j < height; j++)
    for (unsigned int i = 0; i < width; i++)
      if ( (j + y) < values.size() && (i + x) < values[j].size() )
        values[j + y][i + x] = 1.0;
}

void StackItem::print()
{
  for (unsigned int j = 0; j < values.size(); j++)
  {
    for (unsigned int i = 0; i < values[j].size(); i++)
    {
      if (values[j][i] > 0.0)
        printf("*");
      else
        printf(".");
      printf(" ");
    }
    printf("\n");
  }
  printf("\n");
}

void StackItem::process(bool move)
{
  if (move == false)
    state = 2;

  switch (state)
  {
    case 0:
            position++;
            if (position >= (position_max - dimension_max))
              state = 1;
            break;

    case 1:
            position--;
            if (position <= 0)
              state = 0;
            break;

    case 2:
            break;
  }

  if (state != 2)
  {
    if ((move_type%2) == 0)
    {
      this->x = target_x;
      this->y = position;
    }
    else
    {
      this->x = position;
      this->y = target_y;
    }
  }

  set_position();
}


float StackItem::compute_overlap(StackItem &other)
{
  float max_count = 0.0;
  float overlap_count = 0.0;

  for (unsigned int j = 0; j < values.size(); j++)
    for (unsigned int i = 0; i < values[j].size(); i++)
      if (values[j][i] > 0.0)
        max_count++;

  for (unsigned int j = 0; j < values.size(); j++)
    for (unsigned int i = 0; i < values[j].size(); i++)
      if (values[j][i] > 0.0)
      if (other.values[j][i] > 0.0)
        overlap_count++;

  return overlap_count/(max_count + 0.00000001);
}

void StackItem::process_overlap(StackItem &other)
{

  for (unsigned int j = 0; j < values.size(); j++)
    for (unsigned int i = 0; i < values[j].size(); i++)
    {
      if ((values[j][i] > 0.0) && (other.values[j][i] > 0.0))
        values[j][i] = 1.0;
      else
        values[j][i] = 0.0;
    }


  width = 0;
  for (unsigned int j = 0; j < values.size(); j++)
  {
    unsigned int cnt = 0;
    for (unsigned int i = 0; i < values[0].size(); i++)
      if (values[j][i] > 0.0)
        cnt++;
    if (cnt > width)
      width = cnt;
  }

  height = 0;
  for (unsigned int i = 0; i < values[0].size(); i++)
  {
    unsigned int cnt = 0;
    for (unsigned int j = 0; j < values.size(); j++)
      if (values[j][i] > 0.0)
        cnt++;
    if (cnt > height)
      height = cnt;
  }
}
