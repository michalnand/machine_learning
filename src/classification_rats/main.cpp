#include <dataset_landsat.h>
#include <dataset_mnist.h>
#include <dataset_rats.h>


#include <stdio.h>
#include <iostream>
#include <math_.h>
#include <vector>

#include <fnn_extended.h>
#include <classification_compare.h>


void network_train(CDatasetInterface *dataset)
{
  FNNExtended nn;
  nn.load_from_file("net_0", dataset->get_input_size(), dataset->get_output_size());

  unsigned int learning_iterations_max = dataset->get_training_size()*5000;

  for (unsigned int iteration = 0; iteration < learning_iterations_max; iteration++)
  {
    sDatasetItem item;
    item = dataset->get_random_training(0.01);

    nn.learn(&item.output[0], &item.input[0]);

    if ((iteration%100) == 0)
      printf("learning done %6.3f %%\n", iteration*100.0/learning_iterations_max);
  }

  nn.save_to_file("net_0_trained");
}


void network_test(CDatasetInterface *dataset)
{
  FNNExtended nn;
  nn.load_from_file("net_0_trained");

  unsigned int testing_items_count = dataset->get_testing_size();

  CClassificationCompare compare(dataset->get_output_size());
  std::vector<float> nn_output;
  nn_output.resize(dataset->get_output_size());
  for (unsigned int idx = 0; idx < testing_items_count; idx++)
  {
    sDatasetItem item;
    item = dataset->testing[idx];

    nn.forward(&nn_output[0], &item.input[0]);

    // if ((idx%10) == 0)
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


int main()
{
  math.srand(time(NULL));

   CDatasetRats dataset("/home/michal/dataset/rats/rats.txt", 0.5);

/*
   for (unsigned int i = 0; i < dataset.get_training_size(); i++)
   {
    dataset.print_training_item(i);
    printf("\n\n\n");
  }
*/

   network_train(&dataset);
   network_test(&dataset);


  printf("program done\n");

  return 0;
}
