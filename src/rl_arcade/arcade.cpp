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
  {
    reward = -1.0;
    add_wrong();
  }
  else
  {
    for (unsigned int i = 0; i < geometry.h; i++)
      if (screen[i][x] < -0.99)
      {
        reward = 1.0/(geometry.h-2);

        add_best();
        break;
      }
  }

  add_score(reward);

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

  std::string s_summary;
  std::string s_best_total;
  std::string s_best_now;

  s_summary+= "score = " + std::to_string(get_score());
  s_best_total+= "  best total = " + std::to_string(get_best_total()*100.0) + "%";
  s_best_now  += "  best now   = " + std::to_string(get_best_now()*100.0) + "%";


  gl_visualisation.set_color(1.0, 1.0, 0.0);

  gl_visualisation.print(-1.2, -0.7, z_ofs, s_summary);
  gl_visualisation.print(-1.2, -0.9, z_ofs, s_best_total);
  gl_visualisation.print(-1.2, -1.0, z_ofs, s_best_now);



  gl_visualisation.finish();

  printf("%u : %6.3f %6.5f %6.5f %%\n", iteration, get_score(), get_score_filtered(), get_best_now()*100.0);

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
    unsigned int tmp = geometry.h*0.75;
    unsigned int obstacle_height = math.rand()%tmp;
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
