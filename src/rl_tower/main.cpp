#include <stdio.h>

#include <arena.h>
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

  Arena env;

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

/*
  RL_HFNN_Agent agent(&env, "fnn");


  for (unsigned int i = 0; i < 200000; i++)
  {
    agent.process_learn();
    env.visualisation();
    if ((iteration%100000) == 0)
      agent.save("fnn_trained");

    if ((iteration%1000) == 0)
      env.log();
    iteration++;
  }

  agent.save("fnn_trained");
*/

/*
  RL_FNN_Agent agent(&env, "fnn_trained/supervised");

  for (unsigned int i = 0; i < 40000; i++)
  {
    agent.process();
    env.visualisation();
    //timer.sleep_ms(10);
    if ((iteration%1000) == 0)
      env.log();
    iteration++;
  }
*/

  printf("program done\n");

  return 0;
}
