#include <stdio.h>
#include <string>
#include <vector>
#include <math_.h>
#include <timer.h>
#include <getch.h>
#include <iostream>


#include <i_rl_agent.h>
#include <fnn_rl_agent.h>
#include <hfnn_rl_agent.h>
#include <stack_game.h>


void fnn_test(unsigned int idx, unsigned int training_iterations = 5000000, unsigned int testing_iterations = 50000)
{
  std::string agent_parameters;
  std::string training_progress_log;
  std::string testing_progress_log;
  std::string network_result;

  agent_parameters = "parameters/fnn_" + std::to_string(idx);

  training_progress_log = "results/fnn_progress/training_" + std::to_string(idx) + ".log";
  testing_progress_log  = "results/fnn_progress/testing_" + std::to_string(idx) + ".log";
  network_result        = "results/fnn_trained_" + std::to_string(idx);

  unsigned int iteration;

  std::string window_label;

  window_label = "fnn_test :" + std::to_string(idx);

  StackGame env(21,21, false);

  RL_HFNN_Agent agent(&env, agent_parameters);

  iteration = 0;

  for (unsigned int i = 0; i < training_iterations; i++)
  {
    agent.process_learn();
    if ((iteration%10000) == 0)
    {
      printf("saving\n");
      agent.save(network_result);
    }

    if ((iteration%1000) == 0)
    {
      printf(">>>> %u %f %f\n", iteration, env.get_score(), env.get_score_filtered());
      env.log(training_progress_log);
    }
    iteration++;
  }

  agent.save(network_result);

  printf("training done\n");

  RL_FNN_Agent agent_trained(&env, network_result+"/supervised");
  iteration = 0;

  env.init();

  for (unsigned int i = 0; i < testing_iterations; i++)
  {
    agent_trained.process();
    if ((iteration%100) == 0)
      env.log(testing_progress_log);
    iteration++;
  }
}





void hnn_test(unsigned int idx, unsigned int training_iterations = 300000, unsigned int testing_iterations = 50000)
{
  std::string agent_parameters;
  std::string training_progress_log;
  std::string testing_progress_log;
  std::string network_result;

  training_progress_log = "results/hnn_progress/training_" + std::to_string(idx) + ".log";
  testing_progress_log  = "results/hnn_progress/testing_" + std::to_string(idx) + ".log";
  network_result        = "results/hnn_trained_" + std::to_string(idx);

  unsigned int iteration;

  StackGame env(21,21);

  agent_parameters = "parameters/hnn_" + std::to_string(idx);

  RL_HFNN_Agent agent(&env, agent_parameters);

  iteration = 0;

  env.init();

  for (unsigned int i = 0; i < training_iterations; i++)
  {
    agent.process_learn();
    if ((iteration%10000) == 0)
      agent.save(network_result);

    if ((iteration%1000) == 0)
    {
      printf("iteration %u\n", i);
      env.log(training_progress_log);
    }
    iteration++;
  }

  agent.save(network_result);

/*
  RL_FNN_Agent agent_trained(&env, network_result+"/supervised");

  iteration = 0;

  env.init();

  for (unsigned int i = 0; i < testing_iterations; i++)
  {
    agent_trained.process();
    env.visualisation();
    if ((iteration%1000) == 0)
      env.log(testing_progress_log);
    iteration++;
  }
*/
}

void rl_test()
{
  std::string network_result;

  network_result = "results/fnn_trained_0";

  unsigned int iteration = 0;
  unsigned int testing_iterations = 10000;

  StackGame env(21,21);

  RL_FNN_Agent agent_trained(&env, network_result+"/supervised");

  env.init();

  for (unsigned int i = 0; i < testing_iterations; i++)
  {
    agent_trained.process();
    /*
    if ((iteration%1000) == 0)
      env.log(testing_progress_log);
    */
    iteration++;
  }
}


void stack_manual(unsigned int size)
{
  StackGame stack(size, size);

  unsigned int action = 0;

  while (1)
  {
    action = 0;

    if (getch() == ' ')
      action = 1;


    stack.do_action(action);
    timer.sleep_ms(100);
  }
}


int main(int argc, char *argv[])
{
  math.srand(time(NULL));

  fnn_test(0);
//   hnn_test(0);

//  rl_test();
  return 0;
}
