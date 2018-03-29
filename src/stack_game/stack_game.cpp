#include "stack_game.h"

#include <math_.h>
#include <math.h>

StackGame::StackGame(unsigned int width,
             unsigned int height)
{
  this->width  = width;
  this->height = height;

  init();
}

void StackGame::init()
{
  for (unsigned int i = 0; i < items.size(); i++)
    delete items[i];
  items.clear();

  this->item_width  = width-10;
  this->item_height = height-10;

  items.push_back(new StackItem(width, height, item_width, item_height));
  items.push_back(new StackItem(*items[0]));

  overlap = 0.0;
  overlap_filtered = 1.0;
}

StackGame::~StackGame()
{
  for (unsigned int i = 0; i < items.size(); i++)
    delete items[i];

}

void StackGame::action(unsigned int action_id)
{
  unsigned int last = items.size()-1;
  overlap = get_overlap();

  float k = 0.99;
  overlap_filtered = (1.0 - k)*overlap_filtered + k*overlap;
/*
  printf("overlap %6.3f %% [%u %u][%u %u]\n",
                                              overlap*100.0,
                                              items[last]->x,
                                              items[last]->y,
                                              items[last-1]->x,
                                              items[last-1]->y);
*/
  if (action_id == 1)
  {
    items[last]->process_overlap(*items[last-1]);

    if (items[last]->compute_overlap(*items[last-1]) < 0.0001)
      init();
    else
      items.push_back(new StackItem(*items[last]));

    printf("score = %u average overlap %6.3f %%\n", items.size(), overlap_filtered*100.0);
  }


  for (unsigned int i = 0; i < items.size(); i++)
  {
    bool move = false;
    if (i == items.size()-1)
      move = true;
    items[i]->process(move);
  }


  draw();
}

float StackGame::get_overlap()
{
  unsigned int last = items.size()-1;
  return items[last]->compute_overlap(*items[last-1]);
}

float angle = 0.0;

void StackGame::draw()
{
  visualisation.start();

  angle = angle + 0.1;
  unsigned int view_count = 50;
  for (unsigned int i = 0; i < items.size(); i++)
    if ((items.size() < view_count) || (i > (items.size()-view_count)))
    draw_item(i);

  visualisation.finish();
}

void StackGame::draw_item(unsigned int idx)
{
  float cube_size = 0.06;

  int height = items[idx]->values.size();
  int width  = items[idx]->values[0].size();

  visualisation.push();

  float x_ofs = 0.0;
  float y_ofs = -0.5*cube_size*(items.size() - idx) + 0.3;
  float z_ofs = -4.0;

  visualisation.translate(x_ofs, y_ofs, z_ofs);
  visualisation.rotate(40.0, 45.0 + angle, 0.0);


  for (int j = 0; j < height; j++)
    for (int i = 0; i < width; i++)
    {
      if (items[idx]->values[j][i] > 0.0)
      {
        visualisation.push();


        float x = (i - width/2.0)*1.2*cube_size;
        float y = 0.0;
        float z = -(j - height/2.0)*1.2*cube_size;

        int steps = 100;

        float phase = (2.0*3.141592654*(idx%steps))/steps;

        float r = sin(phase + 0.0*2.0*3.141592654);
        float g = sin(phase + 0.3333*2.0*3.141592654);
        float b = sin(phase + 0.6666*2.0*3.141592654);

        visualisation.set_color(r, g, b);

        visualisation.translate(x, y, z);
        visualisation.draw_cube(cube_size);

        visualisation.pop();
      }
    }
  visualisation.pop();
}

bool StackGame::game_over()
{
  if ((item_width <= 1)||
      (item_height <= 1))
     return true;

  return false;
}
