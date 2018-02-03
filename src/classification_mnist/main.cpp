#include <dataset_landsat.h>
#include <dataset_mnist.h>
#include <dataset_mnist_tiny.h>

#include <classification_experiment.h>


int main()
{
  printf("starting\n");
  CDatasetMnistTiny dataset("/home/michal/dataset/mnist_tiny/training.bin",
                            "/home/michal/dataset/mnist_tiny/testing.bin");


  /*
  ClassificationExperiment experiment_00("experiment_parameters/experiment_0.json", &dataset);
  experiment_00.run();

  ClassificationExperiment experiment_01("experiment_parameters/experiment_1.json", &dataset);
  experiment_01.run();

  experiment_00.join();
  experiment_01.join();
  */


  ClassificationExperiment experiment_02("experiment_parameters/experiment_2.json", &dataset);
  experiment_02.run();

  ClassificationExperiment experiment_03("experiment_parameters/experiment_3.json", &dataset);
  experiment_03.run();


  experiment_02.join();
  experiment_03.join();

  printf("program done\n");
  return 0;
}
