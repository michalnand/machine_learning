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
  std::string agent_parameters;
  std::string training_progress_log;
  std::string testing_progress_log;
  std::string network_result;

  agent_parameters = "parameters/fnn_" + std::to_string(idx);

  training_progress_log = "results_sarsa/fnn_progress/training_" + std::to_string(idx) + ".log";
  testing_progress_log  = "results_sarsa/fnn_progress/testing_" + std::to_string(idx) + ".log";
  network_result        = "results_sarsa/fnn_trained_" + std::to_string(idx);

  unsigned int iteration;

  std::string window_label;

  window_label = "fnn_test :" + std::to_string(idx);

  Arcade env(&window_label);

  RL_HFNN_Agent agent(&env, agent_parameters);

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

  env.init();

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
  std::string agent_parameters;
  std::string training_progress_log;
  std::string testing_progress_log;
  std::string network_result;

  training_progress_log = "results_sarsa/hnn_progress/training_" + std::to_string(idx) + ".log";
  testing_progress_log  = "results_sarsa/hnn_progress/testing_" + std::to_string(idx) + ".log";
  network_result        = "results_sarsa/hnn_trained_" + std::to_string(idx);

  unsigned int iteration;

  std::string window_label;

  window_label = "hnn_test :" + std::to_string(idx);

  Arcade env(&window_label);

  agent_parameters = "parameters/hnn_" + std::to_string(idx);

  RL_HFNN_Agent agent(&env, agent_parameters);

  iteration = 0;

  env.init();

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

  env.init();

  for (unsigned int i = 0; i < testing_iterations; i++)
  {
    agent_trained.process();
    env.visualisation();
    if ((iteration%1000) == 0)
      env.log(testing_progress_log);
    iteration++;
  }

}


void run_demo(std::string network_path)
{
  Arcade env(&network_path);

  RL_FNN_Agent agent_trained(&env, network_path+"/supervised");

  while (1)
  {
    agent_trained.process();
    env.visualisation();
    //timer.sleep_ms(10);
  }
}


void manual_controll()
{
  std::string label = "human player";
  Arcade env(&label);

  env.visualisation();

  printf("\n\n\npress any key ...\n");

  while (getch() <= 0)
    timer.sleep_ms(10);

  while (1)
  {
    int c = 0;

    for (unsigned int i = 0; i < 10; i++)
    {
      timer.sleep_ms(5);
      int c_tmp = getch();
      if (c_tmp >= 0)
        c = c_tmp;
    }

    unsigned int action = 0;

    if (c == 27)
      break;
    else
    if ((c == 'r')||(c == 'R'))
      env.init();
    else
    if (c == ' ')
      action = 1;
    else
      action = 0;

    env.do_action(action);
    env.visualisation();

  }
}

int main(int argc, char *argv[])
{

  /*
  if (argc == 2)
  {
    if (*argv[1] == '0')
      run_demo("results/fnn_trained_0");

    if (*argv[1] == '1')
      run_demo("results/hnn_trained_3");

    if (*argv[1] == '2')
      manual_controll();
  }
*/

  if (argc == 1)
  {
    math.srand(time(NULL));

    unsigned int training_iterations = 300000;
    unsigned int testing_iterations  = 50000;


    for (unsigned int i = 0; i < 10; i++)
    {
      fnn_test(i, training_iterations, testing_iterations);
      hnn_test(i, training_iterations, testing_iterations);
    }
  }

  printf("program done\n");

  return 0;
}
