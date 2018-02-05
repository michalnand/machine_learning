#include "worms_arena.h"
#include <stdio.h>
#include <math_.h>

WormsArena::WormsArena()
      :IRLEnvironment()
{
  init();
}

WormsArena::~WormsArena()
{

}

int WormsArena::init()
{
  actions_count = 3;

  geometry.w = 8;
  geometry.h = 1;
  geometry.d = 1;

  x = math.rnd();
  y = math.rnd();
  dx = 0.0;
  dy = 0.0;

  state.init(geometry);

  update_state();
  iteration = 0;

  food.init(30, &gl_visualisation);
  worm.init(x, y, 50, 1.0, 0.0, 0.0, &gl_visualisation);

  return 0;
}

void WormsArena::do_action(unsigned int action_id)
{
  if (math.abs(math.rnd()) < 0.01)
  {
    dx = math.rnd()*0.01;
    dy = math.rnd()*0.01;
  }
  
  worm.move(dx, dy);

  if (
      (math.abs(worm.x) > 1.5)||
      (math.abs(worm.y) > 1.5) )
  {
    worm.x = math.rnd();
    worm.y = math.rnd();
    reward = -1.0;
  }

  float res = food.eat(worm.x, worm.y);
  if (res > 0.0)
    reward = 1.0;

  score+= reward;
  visualisation();
}

void WormsArena::visualisation()
{
  gl_visualisation.start();

  food.paint();
  worm.paint();

  std::string info;
  info+= "score = " + std::to_string(score);

  if (score < 0.0)
    gl_visualisation.set_color(0.0, 0.0, 1.0);
  else
    gl_visualisation.set_color(1.0, 0.0, 0.0);

  gl_visualisation.print(0, -1, -3.0, info);

  gl_visualisation.finish();
}

void WormsArena::log()
{

}

void WormsArena::update_state()
{

}
