#include <dataset_stack.h>
#include <fnn.h>
#include <classification_compare.h>

#include <stdio.h>
#include <string>
#include <vector>
#include <math_.h>

int main()
{
  math.srand(time(NULL));

  unsigned int training_count = 100000;
  unsigned int testing_count  = 10000;
  unsigned int unlabeled_count  = 0;

  DatasetStack dataset(32, 32, training_count, testing_count, unlabeled_count, 0.5, 0.1, 0.5);

  sFNNInit nn_init;

  nn_init.input_size  = dataset.get_input_size();
  nn_init.output_size = dataset.get_output_size();
  nn_init.activation_function = FNN_RELU_LAYER;

  nn_init.hyperparameters.learning_rate = 0.0001;
  nn_init.hyperparameters.lambda = 0.0;
  nn_init.hyperparameters.dropout = 0.0;
  nn_init.hyperparameters.init_weight_range = 0.01;


  nn_init.hidden_layers.push_back(256);
/*
  nn_init.hidden_layers.push_back(32);
*/
  FNN nn;
  nn.init(nn_init);

  unsigned int training_iterations = training_count*10;

  for (unsigned int i = 0; i < training_iterations; i++)
  {
    sDatasetItem item = dataset.get_random_training();
    nn.learn(&item.output[0], &item.input[0]);

    printf("training done %6.3f %%\n", i*100.0/training_iterations);
  }




  ClassificationCompare compare(dataset.get_output_size());

  std::vector<float> nn_output;
  nn_output.resize(dataset.get_output_size());

  for (unsigned int i = 0; i < dataset.get_testing_size(); i++)
  {
    sDatasetItem ground_truth = dataset.testing[i];

    nn.forward(&nn_output[0], &ground_truth.input[0]);

    compare.compare(&ground_truth.output[0], &nn_output[0]);
  }

  compare.process(true);

  std::string result = compare.get_text_result();

  printf("\n\n\n%s\n\n", result.c_str());
  printf ("program done\n");


  printf ("program done\n");

  return 0;
}
