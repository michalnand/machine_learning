#include <stdio.h>
#include <iostream>

#include <math_.h>
#include <log.h>
#include <timer.h>
#include <vector>

#include <fnn_extended.h>
#include <fnn_heterogeneous.h>

#include <dataset_landsat.h>
#include <dataset_mnist.h>
#include <dataset_mnist_tiny.h>
#include <classification_compare.h>


void network_train(CDatasetInterface *dataset)
{
  FNNExtended nn;

  nn.load_from_file("my_net", dataset->get_input_size(), dataset->get_output_size());
  nn.set_epoch_size(dataset->get_training_size());


  timer.start();
  unsigned int iteration = 0;
  while (nn.training_done() != true)
  {
    sDatasetItem item;
    item = dataset->get_random_training(0.01);

    nn.learn(&item.output[0], &item.input[0]);

    if ((iteration%100) == 0)
      printf("learning done %6.3f %%\n", 100.0*nn.get_training_progress());
    iteration++;
  }
  timer.stop();

  printf("training total time %f [s]\n", timer.get_duration()/1000.0);

  nn.save_to_file("my_net_trained");
}




void hn_network_train(CDatasetInterface *dataset)
{
  FNNHeterogeneous nn;
  nn.load_from_file("my_net", dataset->get_input_size(), dataset->get_output_size());

  nn.set_unsupervised_epoch_size(dataset->get_training_size());
  nn.set_supervised_epoch_size(dataset->get_training_size());

  unsigned int iteration = 0;
  timer.start();


  while (nn.unsupervised_training_done() != true)
  {
    sDatasetItem item;
    item = dataset->get_random_training(0.01);
 
    nn.learn_unsupervised(&item.input[0]);

    if ((iteration%1000) == 0)
      printf("unsupervised learning done %6.3f %%\n", 100.0*nn.get_unsupervised_training_progress());
    iteration++;
  }

  nn.fnn_update_weights();
  nn.save_to_file("my_net_trained");

  while (nn.supervised_training_done() != true)
  {
    sDatasetItem item;
    item = dataset->get_random_training(0.01);

    nn.learn(&item.output[0], &item.input[0]);

    if ((iteration%1000) == 0)
      printf("supervised learning done %6.3f %%\n", 100.0*nn.get_supervised_training_progress());
    iteration++;
  }

  nn.save_to_file("my_net_trained");


  timer.stop();
  printf("training total time %f [s]\n", timer.get_duration()/1000.0);
  nn.save_to_file("my_net_trained");
}

void network_test(CDatasetInterface *dataset)
{
  FNNExtended nn;
  nn.load_from_file("my_net_trained/supervised");

  unsigned int testing_items_count = dataset->get_testing_size();

  CClassificationCompare compare(dataset->get_output_size());
  std::vector<float> nn_output;
  nn_output.resize(dataset->get_output_size());

  timer.start();
  for (unsigned int idx = 0; idx < testing_items_count; idx++)
  {
    sDatasetItem item;
    item = dataset->testing[idx];

    nn.forward(&nn_output[0], &item.input[0]);


    if ((idx%100) == 0)
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
  timer.stop();


  compare.process(true);
  std::string result = compare.get_text_result();

  std::cout << result;

  printf("forward total time %f [s]\n", timer.get_duration()/1000.0);
}

int main()
{
  math.srand(time(NULL));


CDatasetMnistTiny dataset("/home/michal/dataset/mnist_tiny/training.bin",
                          "/home/michal/dataset/mnist_tiny/testing.bin");

 hn_network_train(&dataset);

 network_test(&dataset);

  printf("program done\n");

  return 0;
}
