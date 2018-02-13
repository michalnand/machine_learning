#include <stdio.h>

#include <arcade.h>
#include <i_rl_agent.h>
#include <fnn_rl_agent.h>
#include <hfnn_rl_agent.h>

#include <math_.h>
#include <timer.h>
#include <getch.h>



int main()
{
  math.srand(time(NULL));

  Arcade env;

  RL_HFNN_Agent agent(&env, "hybrid_fnn");


  unsigned int iteration = 0;
  for (unsigned int i = 0; i < 200000; i++)
  {
    agent.process_learn();
    env.visualisation();

/*
    if ((iteration%300000) < 1000)
      timer.sleep_ms(20);
*/
    if ((iteration%100000) == 0)
      agent.save("hybrid_fnn_trained");

    if ((iteration%1000) == 0)
      env.log();
    iteration++;
  }

  agent.save("hybrid_fnn_trained");


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
