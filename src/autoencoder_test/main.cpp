#include <stdio.h>
#include <iostream>

#include <math_.h>
#include <vpu.h>
#include <log.h>
#include <timer.h>
#include <vector>

#include <fnn_extended.h>
#include <fnn_autoencoder.h>

#include <fnn_autoencoder_extended.h>

#include <dataset_landsat.h>
#include <dataset_mnist.h>
#include <dataset_mnist_tiny.h>


void network_train(DatasetInterface *dataset)
{
  FNNAutoencoderExtended nn;

  nn.load_from_file("autoencoder", dataset->get_input_size());
  nn.set_epoch_size(dataset->get_training_size());

  timer.start();
  unsigned int iteration = 0;
  while (nn.training_done() != true)
  {
    sDatasetItem item;
    item = dataset->get_random_training(0.01);

    nn.learn(&item.input[0]);

    if ((iteration%100) == 0)
      printf("learning done %6.3f %% depth %u\n", 100.0*nn.get_training_progress(), nn.get_current_depth());

    if ((iteration%dataset->get_training_size()) == 0)
    {
      nn.save_to_file("autoencoder_trained");
    }

    iteration++;
  }
  timer.stop();

  printf("training total time %f [s]\n", timer.get_duration()/1000.0);
  nn.save_to_file("autoencoder_trained");




  unsigned int testing_items_count = dataset->get_testing_size();

  std::vector<float> nn_output;
  nn_output.resize(dataset->get_input_size());

  timer.start();

  float error_sum = 0.0;
  for (unsigned int idx = 0; idx < testing_items_count; idx++)
  {
    sDatasetItem item;
    item = dataset->testing[idx];

    nn.forward(&nn_output[0], &item.input[0]);

    float error = vpu.vector_dist(&nn_output[0], &item.input[0], nn_output.size());
    error_sum+= error/nn_output.size();

    if ((idx%100) == 0)
    {
      unsigned int width = dataset->get_width();
      unsigned int height = dataset->get_height();

      std::string input_image_file_name = "images/"+std::to_string(idx)+"_in.png";
      std::string output_image_file_name = "images/"+std::to_string(idx)+"_out.png";

      Image input_image(width, height);
      Image output_image(width, height);

      input_image.from_vector_grayscale(item.input);
      output_image.from_vector_grayscale(nn_output);

      input_image.save(input_image_file_name);
      output_image.save(output_image_file_name);
    }

    printf("done %6.3f %%, error %f\n", idx*100.0/testing_items_count, error_sum/testing_items_count);
  }
  timer.stop();

  printf("total error %f\n", error_sum/testing_items_count);
  printf("testing time %f [s]\n", timer.get_duration()/1000.0);
}


int main()
{
  math.srand(time(NULL));
/*
  DatasetMnist dataset("/home/michal/dataset/mnist/train-images.idx3-ubyte",
                        "/home/michal/dataset/mnist/train-labels.idx1-ubyte",
                        "/home/michal/dataset/mnist/t10k-images.idx3-ubyte",
                        "/home/michal/dataset/mnist/t10k-labels.idx1-ubyte");
*/

  DatasetMnistTiny dataset("/home/michal/dataset/mnist_tiny/training.bin",
                            "/home/michal/dataset/mnist_tiny/testing.bin");

  network_train(&dataset);


  printf("program done\n");

  return 0;
}
