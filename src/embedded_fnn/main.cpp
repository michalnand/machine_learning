#include <stdio.h>
#include <iostream>

#include <timer.h>
#include <vector>
#include <dataset_mnist_tiny.h>
#include <classification_compare.h>

#include <tiny_net/tiny_net.h>

#include <hardware_in_loop.h>

void nn_set_input_from_float(std::vector<float> &input)
{
  for (unsigned int i = 0; i < nn.get_input_size(); i++)
  {
    int tmp = input[i]*TINY_NET_ONE;
    nn.input[i] = tmp;
  }
}

std::vector<float> nn_get_output_to_float()
{
  std::vector<float> result;

  for (unsigned int i = 0; i < nn.get_output_size(); i++)
      result.push_back(nn.output[i]*1.0/TINY_NET_ONE);

  return result;
}


void network_test(CDatasetInterface *dataset)
{
  unsigned int testing_items_count = dataset->get_testing_size();

  CClassificationCompare compare(dataset->get_output_size());

  std::vector<float> nn_output;
  nn_output.resize(dataset->get_output_size());

  nn.init();

  timer.start();
  for (unsigned int idx = 0; idx < testing_items_count; idx++)
  {
    sDatasetItem item;
    item = dataset->testing[idx];

    nn_set_input_from_float(item.input);

    nn.process();

    std::vector<float> nn_output = nn_get_output_to_float();


    compare.compare(&item.output[0], &nn_output[0]);
    if ((idx%200) == 0)
    {
      for (unsigned int i = 0; i < item.input.size(); i++)
        printf("%i ", nn.input[i]);
      printf("\n>\n");
      for (unsigned int i = 0; i < item.output.size(); i++)
        printf("%i ", nn.output[i]);
      printf("\n\n\n");
    }
    /*
    if ((idx%200) == 0)
    {
      for (unsigned int i = 0; i < item.output.size(); i++)
        printf("%6.3f ", item.output[i]);

      printf(" >> ");

      for (unsigned int i = 0; i < nn_output.size(); i++)
        printf("%6.3f ", nn_output[i]);

      printf("\n");
    }
    */
  }
  timer.stop();


  compare.process(true);
  std::string result = compare.get_text_result();

  std::cout << result;

  printf("forward total time %f [s]\n", timer.get_duration()/1000.0);
}




void network_test_hw_in_loop(CDatasetInterface *dataset)
{
  unsigned int testing_items_count = dataset->get_testing_size();

  CClassificationCompare compare(dataset->get_output_size());

  HardwareInLoop hw_in_loop;

  sleep(3);
  printf("starting\n");

  timer.start();
  for (unsigned int i = 0; i < 1000; i++)
  {
    unsigned int idx = rand()%testing_items_count;
    sDatasetItem item;
    item = dataset->testing[idx];

    hw_in_loop.send(item.input);
    std::vector<float> nn_output = hw_in_loop.get();


    for (unsigned int i = 0; i < item.output.size(); i++)
      printf("%6.3f ", item.output[i]);

    printf(" >> ");

    for (unsigned int i = 0; i < nn_output.size(); i++)
      printf("%6.3f ", nn_output[i]);

    printf("\n");

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
  CDatasetMnistTiny dataset("/home/michal/dataset/mnist_tiny/training.bin",
                            "/home/michal/dataset/mnist_tiny/testing.bin");

// network_test(&dataset);
  network_test_hw_in_loop(&dataset);

  printf("program done\n");

  return 0;
}
