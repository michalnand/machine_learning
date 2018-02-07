#include "arcade.h"
#include <stdio.h>
#include <math_.h>
#include <vpu.h>

Arcade::Arcade()
      :IRLEnvironment()
{
  init();
}

Arcade::~Arcade()
{

}

int Arcade::init()
{
  obstacle_density = 0.1;
  actions_count = 2;

  geometry.w = 19;
  geometry.h = 5;
  geometry.d = 1;

  x = 1;
  y = 0;
  move_state = 0;

  screen.resize(geometry.h);
  for (unsigned int i = 0; i < screen.size(); i++)
    screen[i].resize(geometry.w);

  for (unsigned int j = 0; j < screen.size(); j++)
    for (unsigned int i = 0; i < screen[j].size(); i++)
      screen[j][i] = 0.0;

  state.init(geometry);

  iteration = 0;
  score_filtered = 0.0;

  update_state();
  return 0;
}

void Arcade::do_action(unsigned int action_id)
{

  switch (move_state)
  {
    case 0:
            if (action_id == 1)
              move_state = 1;
            break;

    case 1: if (y < geometry.h-1)
              y++;
            else
              move_state = 2;
            break;

    case 2: if (y > 0)
              y--;
            else
              move_state = 0;
            break;

  }

  update_state();

  reward = 0.0;
  if (screen[y][x] < -0.99)
    reward = -1.0;
  else
  {
    for (unsigned int i = 0; i < geometry.h; i++)
      if (screen[i][x] < -0.99)
      {
        reward = 1.0/(geometry.h-2);
        break;
      }
  }

  score+= reward;

  float k = 0.999;
  score_filtered = k*score_filtered + (1.0 - k)*reward;

  iteration++;
  
  visualisation();
}

void Arcade::visualisation()
{
  gl_visualisation.start();

  float x_ofs = 0.0;
  float y_ofs = 1.0;
  float z_ofs = -3.0;
  float size = 0.1;

  float step = 1.9/size;

  for (unsigned int j = 0; j < screen.size(); j++)
    for (unsigned int i = 0; i < screen[j].size(); i++)
    {
      float x_ = (i*1.0/step - 0.5)*2.0;
      float y_ = (j*1.0/step - 0.5)*2.0;

      float r = 1.0;
      float g = 1.0;
      float b = 1.0;

      if (screen[j][i] < -0.9)
      {
        r = 1.0;
        g = 0.0;
        b = 0.0;
      }

      if ((j == y) && (i == x))
      {
        r = 0.0;
        g = 1.0;
        b = 0.0;
      }

      gl_visualisation.paint_square( x_ + x_ofs,
                                   y_ + y_ofs,
                                   0 + z_ofs,
                                   size,
                                   r,
                                   g,
                                   b);
    }

  std::string info;
  info+= "score = " + std::to_string(score);
  info+= "  score_filtered = " + std::to_string(score_filtered);


  gl_visualisation.set_color(1.0, 1.0, 0.0);
  gl_visualisation.print(-1.2, -1, -3.0, info);

  gl_visualisation.finish();

  printf("%u : %6.3f %6.5f\n", iteration, score, score_filtered);

}

void Arcade::update_state()
{
  for (unsigned int j = 0; j < geometry.h; j++)
  for (unsigned int i = 0; i < (geometry.w-1); i++)
      screen[j][i] = screen[j][i+1];

  for (unsigned int j = 0; j < geometry.h; j++)
    screen[j][geometry.w-1] = 0.0;


  if (math.abs(math.rnd()) < obstacle_density)
  {
    unsigned int obstacle_height = math.rand()%(geometry.h-2);
    for (unsigned int j = 0; j < obstacle_height; j++)
      screen[j][geometry.w-1] = -1.0;
  }

  unsigned int ptr = 0;

  for (unsigned int j = 0; j < geometry.h; j++)
    for (unsigned int i = 0; i < geometry.w; i++)
    {
      state.state[ptr] = screen[j][i];
      ptr++;
    }

  unsigned int idx = x + y*state.geometry.w;
  state.state[idx] = 1.0;

  /*
  ptr = 0;
  for (unsigned int j = 0; j < geometry.h; j++)
  {
    for (unsigned int i = 0; i < geometry.w; i++)
    {
      printf("%4.1f ", state.state[ptr]);
      ptr++;
    }
    printf("\n");
  }
  printf("\n\n");
  */
}
