#include <stdio.h>

#include <worms_arena.h>
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

  training_progress_log = "results/fnn_progress/training_" + std::to_string(idx) + ".log";
  testing_progress_log  = "results/fnn_progress/testing_" + std::to_string(idx) + ".log";
  network_result        = "results/fnn_trained_" + std::to_string(idx);

  unsigned int iteration;

  std::string window_label;

  window_label = "fnn_test :" + std::to_string(idx);

  WormsArena env;

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
/*
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

  WormsArena env;

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
/*
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


void run_demo()
{
  WormsArena env;

  sRLHyperParameters agent_hyperparameters;
  agent_hyperparameters.path_max_length = 100;
  agent_hyperparameters.gamma = 0.98;
  agent_hyperparameters.epsilon = 0.3;
  agent_hyperparameters.path_epochs_count = 10;


  RLState state = env.get_state();

  sFNNInit nn_init;
  nn_init.input_size  = state.geometry.w*state.geometry.h*state.geometry.d;
  nn_init.output_size = env.get_actions_count();
  nn_init.activation_function = FNN_RELU_LAYER;

  nn_init.hyperparameters.learning_rate = 0.001;
  nn_init.hyperparameters.init_weight_range = 0.01;
  nn_init.hyperparameters.dropout = 0.0;
  nn_init.hyperparameters.lambda = 0.000000001;


  nn_init.hidden_layers.push_back(8);


  RL_FNN_Agent agent(&env, agent_hyperparameters, nn_init);

  while (1)
  {
    agent.process_learn();
    env.visualisation();
  }
}

int main()
{
  math.srand(time(NULL));

  unsigned int training_iterations = 300000;
  unsigned int testing_iterations  = 50000;

  for (unsigned int i = 0; i < 10; i++)
  {
    hnn_test(i, training_iterations, testing_iterations);
    fnn_test(i, training_iterations, testing_iterations);
  }


  printf("program done\n");

  return 0;
}
