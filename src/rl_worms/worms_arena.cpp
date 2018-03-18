#include "worms_arena.h"
#include <stdio.h>
#include <math_.h>
#include <vpu.h>

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
  IRLEnvironment::init();

  actions_count = 3;

  geometry.w = 17;
  geometry.h = 1;
  geometry.d = 1;

  x = math.rnd();
  y = math.rnd();
  dx = 0.0;
  dy = 0.0;

  state.init(geometry);

  update_state();
  iteration = 0;

  food.init(50, &gl_visualisation);
  worm.init(x, y, 20, 1.0, 0.0, 0.0, &gl_visualisation);

  score_filtered = 0.0;

  return 0;
} 

void WormsArena::do_action(unsigned int action_id)
{
/*
  std::vector<float> sensors = food.state(worm.x, worm.y, worm.theta);

  unsigned int max_idx = vpu.argmax(&sensors[0], sensors.size());

  action_id = 0;
  if (max_idx < 0.1*sensors.size())
    action_id = 2;
  if (max_idx > 0.9*sensors.size())
    action_id = 1;

  if (math.abs(math.rnd()) < 0.03)
    action_id = math.rand()%3;
  */
  worm.move(action_id);

  reward = 0.0;
  if (
      (math.abs(worm.x) > 2.0)||
      (math.abs(worm.y) > 2.0) )
  {
    worm.respawn();
    reward = -1.0;
  }

  float res = food.eat(worm.x, worm.y);
  if (res > 0.0)
    reward+= 0.1;

  add_score(reward);

  iteration++;


  state.state = food.state(worm.x, worm.y, worm.theta);

  visualisation();
}

void WormsArena::visualisation()
{
  gl_visualisation.start();

  food.paint();
  worm.paint();

  std::string info;
  info+= "score = " + std::to_string(score);
  info+= "  score_filtered = " + std::to_string(score_filtered);

  if (score < 0.0)
    gl_visualisation.set_color(0.0, 0.0, 1.0);
  else
    gl_visualisation.set_color(1.0, 0.0, 0.0);

  gl_visualisation.print(-1.2, -1, -3.0, info);

  gl_visualisation.finish();
}

void WormsArena::update_state()
{

}
