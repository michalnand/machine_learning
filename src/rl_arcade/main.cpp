#include <stdio.h>

#include <arcade.h>
#include <i_rl_agent.h>
#include <fnn_rl_agent.h>
#include <hfnn_rl_agent.h>

#include <math_.h>
#include <timer.h>
#include <getch.h>

void fnn_test(unsigned int idx, unsigned int training_iterations = 300000, unsigned int testing_iterations = 50000)
{
  std::string training_progress_log;
  std::string testing_progress_log;
  std::string network_result;

  training_progress_log = "fnn_progress/training_" + std::to_string(idx) + ".log";
  testing_progress_log  = "fnn_progress/testing_" + std::to_string(idx) + ".log";
  network_result        = "fnn_trained_" + std::to_string(idx);

  unsigned int iteration;

  Arcade env;

  RL_HFNN_Agent agent(&env, "fnn");

  iteration = 0;

  for (unsigned int i = 0; i < training_iterations; i++)
  {
    agent.process_learn();
    env.visualisation();
    if ((iteration%100000) == 0)
      agent.save(network_result);

    if ((iteration%1000) == 0)
      env.log(training_progress_log);
    iteration++;
  }

  agent.save(network_result);


  RL_FNN_Agent agent_trained(&env, network_result+"/supervised");
  iteration = 0;

  for (unsigned int i = 0; i < testing_iterations; i++)
  {
    agent_trained.process();
    env.visualisation();
    if ((iteration%1000) == 0)
      env.log(testing_progress_log);
    iteration++;
  }

}


void hnn_test(unsigned int idx, unsigned int training_iterations = 300000, unsigned int testing_iterations = 50000)
{
  std::string training_progress_log;
  std::string testing_progress_log;
  std::string network_result;

  training_progress_log = "hnn_progress/training_" + std::to_string(idx) + ".log";
  testing_progress_log  = "hnn_progress/testing_" + std::to_string(idx) + ".log";
  network_result        = "hnn_trained_" + std::to_string(idx);

  unsigned int iteration;

  Arcade env;

  RL_HFNN_Agent agent(&env, "hnn");

  iteration = 0;

  for (unsigned int i = 0; i < training_iterations; i++)
  {
    agent.process_learn();
    env.visualisation();
    if ((iteration%100000) == 0)
      agent.save(network_result);

    if ((iteration%1000) == 0)
      env.log(training_progress_log);
    iteration++;
  }

  agent.save(network_result);


  RL_FNN_Agent agent_trained(&env, network_result+"/supervised");

  iteration = 0;

  for (unsigned int i = 0; i < testing_iterations; i++)
  {
    agent_trained.process();
    env.visualisation();
    if ((iteration%1000) == 0)
      env.log(testing_progress_log);
    iteration++;
  }

}

int main()
{ 
  math.srand(time(NULL));

  unsigned int training_iterations = 300000;
  unsigned int testing_iterations  = 50000;

  for (unsigned int i = 0; i < 5; i++)
    fnn_test(i, training_iterations, testing_iterations);

  for (unsigned int i = 0; i < 5; i++)
    hnn_test(i, training_iterations, testing_iterations);

  printf("program done\n");

  return 0;
}
