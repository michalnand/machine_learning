#include "arena.h"
#include <stdio.h>
#include <math_.h>
#include <vpu.h>

Arena::Arena()
      :IRLEnvironment()
{

}

Arena::~Arena()
{

}

int Arena::init(sArenaInit init_struct)
{

  geometry.w = 19;
  geometry.h = 5;
  geometry.d = 1;


  state.init(geometry);


  update_state();
  return 0;
}

void Arena::do_action(unsigned int action_id)
{

}

void Arena::visualisation()
{
  gl_visualisation.start();




  gl_visualisation.finish();


}

void Arena::update_state()
{
}
