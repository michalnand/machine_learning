#include <stdio.h>
#include <iostream>

#include <math_.h>
#include <log.h>
#include <timer.h>
#include <vector>

#include <fnn_extended.h>
#include <fnn_autoencoder_extended.h>

#include <dataset_landsat.h>
#include <dataset_mnist.h>
#include <dataset_mnist_tiny.h>


void network_train(CDatasetInterface *dataset)
{
  sFNNInit fnn_init;

  fnn_init.input_size = dataset->get_input_size();
  fnn_init.output_size = 20;
  fnn_init.activation_function = FNN_LRELU_LAYER;

  fnn_init.hyperparameters.learning_rate = 0.0001;
  fnn_init.hyperparameters.init_weight_range = 0.1;
  fnn_init.hyperparameters.dropout = 0.3;

  //fnn_init.hidden_layers.push_back(64);
  // fnn_init.hidden_layers.push_back(32);


  FNNAutoencoder nn;

  nn.init(fnn_init);

  unsigned int learning_iterations_max = dataset->get_training_size()*10;

  timer.start();
  for (unsigned int iteration = 0; iteration < learning_iterations_max; iteration++)
  {
    sDatasetItem item;
    item = dataset->get_random_training(0.01);

    nn.learn(&item.input[0]);

    if ((iteration%100) == 0)
      printf("learning done %6.3f %%\n", iteration*100.0/learning_iterations_max);
  }
  timer.stop();

  printf("training total time %f [s]\n", timer.get_duration()/1000.0);




  unsigned int testing_items_count = dataset->get_testing_size();

  std::vector<float> nn_output;
  nn_output.resize(dataset->get_input_size());

  timer.start();
  for (unsigned int idx = 0; idx < testing_items_count; idx++)
  {
    sDatasetItem item;
    item = dataset->testing[idx];

    nn.forward(&nn_output[0], &item.input[0]);

    if ((idx%100) == 0)
    {
      unsigned int width = dataset->get_width();
      unsigned int height = dataset->get_height();

      std::string input_image_file_name = "images/"+std::to_string(idx)+"_in.png";
      std::string output_image_file_name = "images/"+std::to_string(idx)+"_out.png";

      CImage input_image(width, height);
      CImage output_image(width, height);

      input_image.from_vector_grayscale(item.input);
      output_image.from_vector_grayscale(nn_output);

      input_image.save(input_image_file_name);
      output_image.save(output_image_file_name);
    }

    printf("done %6.3f %%\n", idx*100.0/testing_items_count);
  }
  timer.stop();

  printf("testing time %f [s]\n", timer.get_duration()/1000.0);
}
int main()
{
  math.srand(time(NULL));
/*
  CDatasetMnist dataset("/home/michal/dataset/mnist/train-images.idx3-ubyte",
                        "/home/michal/dataset/mnist/train-labels.idx1-ubyte",
                        "/home/michal/dataset/mnist/t10k-images.idx3-ubyte",
                        "/home/michal/dataset/mnist/t10k-labels.idx1-ubyte");
*/
  CDatasetMnistTiny dataset("/home/michal/dataset/mnist_tiny/training.bin",
                            "/home/michal/dataset/mnist_tiny/testing.bin");

  network_train(&dataset);


  printf("program done\n");

  return 0;
}
