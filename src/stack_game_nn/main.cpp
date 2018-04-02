#include <dataset_stack.h>
#include <fnn.h>
#include <fnn_extended.h>
#include <classification_compare.h>

#include <stdio.h>
#include <string>
#include <vector>
#include <math_.h>

#include <stack_game.h>
#include <timer.h>
#include <getch.h>
#include <iostream>



void network_train(DatasetInterface *dataset)
{
  FNNExtended nn;
  nn.load_from_file("net", dataset->get_input_size(), dataset->get_output_size());

  unsigned int learning_iterations_max = dataset->get_training_size()*10;

  for (unsigned int iteration = 0; iteration < learning_iterations_max; iteration++)
  {
    sDatasetItem item;
    item = dataset->get_random_training(0.01);

    nn.learn(&item.output[0], &item.input[0]);

    if ((iteration%100) == 0)
      printf("learning done %6.3f %%\n", iteration*100.0/learning_iterations_max);

    if ((iteration%dataset->get_training_size()) == 0)
      nn.save_to_file("net_trained");
  }

  nn.save_to_file("net_trained");
}


void network_test(DatasetInterface *dataset)
{
  FNNExtended nn;
  nn.load_from_file("net_trained");

  unsigned int testing_items_count = dataset->get_testing_size();

  ClassificationCompare compare(dataset->get_output_size());
  std::vector<float> nn_output;
  nn_output.resize(dataset->get_output_size());
  for (unsigned int idx = 0; idx < testing_items_count; idx++)
  {
    sDatasetItem item;
    item = dataset->testing[idx];

    nn.forward(&nn_output[0], &item.input[0]);

    if ((idx%10) == 0)
    {
      for (unsigned int i = 0; i < item.output.size(); i++)
        printf("%6.3f ", item.output[i]);

      printf(" >> ");

      for (unsigned int i = 0; i < nn_output.size(); i++)
        printf("%6.3f ", nn_output[i]);

      printf("\n");
    }

    compare.compare(&item.output[0], &nn_output[0]);
  }

  compare.process(true);
  std::string result = compare.get_text_result();

  std::cout << result;
}


void stack_manual(unsigned int size)
{
  StackGame stack(size, size);

  unsigned int action = 0;

  while (1)
  {
    action = 0;
    /*
    if ((rand()%100) < 1)
      action = 1;

    if (stack.get_overlap() > 0.999999)
      action = 1;
      */

    if (getch() == ' ')
      action = 1;


    stack.do_action(action);
    timer.sleep_ms(100);
  }
}

void stack_nn_bot(unsigned int size)
{
  StackGame stack(size, size);

  FNNExtended nn;
  nn.load_from_file("net_trained");


  unsigned int action = 0;

  std::vector<float> nn_output;
  nn_output.resize(2);

  unsigned int try_count = 50;
  while (1)
  {
    stack.do_action(action);

    nn.forward(&nn_output[0], &stack.get_state().state[0]);

    if (nn_output[1] > nn_output[0])
    {
      action = 1;
      try_count = 50;
    }
    else
    {
      if (try_count != 0)
      {
        try_count--;
        action = 0;
      }
      else
      {
        try_count = 50;
        action = 1;
      }
    }

    timer.sleep_ms(5);
  }
}



int main(int argc, char *argv[])
{
  math.srand(time(NULL));

  unsigned int size = 21;


  if (argc == 2)
  {
   if (argv[1][0] == 'n')
     stack_nn_bot(size);
   if (argv[1][0] == 'm')
    stack_manual(size);
   }
  else
  {
	  unsigned int training_count = 100000;
	  unsigned int testing_count  = 10000;
	  unsigned int unlabeled_count  = 0;

	  DatasetStack dataset(size, size, training_count, testing_count, unlabeled_count, 0.5, 0.1, 0.5);

	  network_train(&dataset);
	  network_test(&dataset);
	  printf ("program done\n");
  }

  return 0;
}
