#include <stdio.h>

#include <arcade.h>
#include <i_rl_agent.h>
#include <fnn_rl_agent_extended.h>

#include <math_.h>
#include <timer.h>
#include <getch.h>



int main()
{
  math.srand(time(NULL));

  Arcade env;


  RL_FNN_Agent_Extended agent(&env, "my_agent");

  unsigned int iteration = 0;
  while (1)
  {
    agent.process_learn();
    env.visualisation();

    if ((iteration%300000) < 1000)
      timer.sleep_ms(20);

    if ((iteration%100000) == 0)
      agent.save("agent_trained");

    iteration++;
  }

/*
  RL_FNN_Agent_Extended agent(&env, "agent_trained_deep");

  while (1)
  {
    agent.process();
    env.visualisation();
    //timer.sleep_ms(10);
  }
*/

  printf("program done\n");

  return 0;
}
