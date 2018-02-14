#include <stdio.h>

#include <go.h>
#include <i_rl_agent.h>
#include <fnn_rl_agent.h>
#include <hfnn_rl_agent.h>

#include <math_.h>
#include <timer.h>
#include <getch.h>



int main()
{
  unsigned int iteration = 0;

  math.srand(time(NULL));

  GO env(19);


  while (1)
  {
    unsigned int action;

    action = rand()%env.get_actions_count();
    env.set_active_player(GO_PLAYER_BLACK);
    env.do_action(action);
    env.visualisation();

    env.set_active_player(GO_PLAYER_WHITE);
    action = rand()%env.get_actions_count();
    env.do_action(action);
    env.visualisation();


    timer.sleep_ms(10);
  }

  /*
  while (1)
  {
    int key = getch();
    unsigned int action = 0;

    if (key == ' ')
      action = 1;

    env.do_action(action);
    env.visualisation();

    timer.sleep_ms(100);
  }
  */

  printf("program done\n");

  return 0;
}
