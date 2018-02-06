#include <stdio.h>

#include <arcade.h>
#include <i_rl_agent.h>
#include <fnn_rl_agent.h>

#include <math_.h>
#include <timer.h>
#include <getch.h>



int main()
{
  math.srand(time(NULL));

  Arcade env;

/*
  while (1)
  {
    env.do_action(math.rand()%2);
    timer.sleep_ms(5);
  }
*/

  sRLHyperParameters agent_hyperparameters;
  agent_hyperparameters.path_max_length = 100;
  agent_hyperparameters.gamma = 0.8;
  agent_hyperparameters.epsilon = 0.05;
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


  nn_init.hidden_layers.push_back(32);

  RL_FNN_Agent agent(&env, agent_hyperparameters, nn_init);

  unsigned int iteration = 0;
  while (1)
  {
    agent.process_learn();
    env.visualisation();

    if ((iteration%300000) < 1000)
      timer.sleep_ms(20);
    iteration++;
    printf("%u\n", iteration);
  }

  printf("program done\n");

  return 0;
}
