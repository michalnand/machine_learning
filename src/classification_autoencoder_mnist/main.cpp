#include <dataset_landsat.h>
#include <dataset_mnist.h>
#include <dataset_mnist_tiny.h>

#include <classification_autoencoder_experiment.h>


int main()
{
  printf("starting\n");

   DatasetMnistTiny dataset("/home/michal/dataset/mnist_tiny/training.bin",
                            "/home/michal/dataset/mnist_tiny/testing.bin");

  std::vector<ClassificationAutoencoderExperiment*> experiments;

  experiments.push_back(new ClassificationAutoencoderExperiment("experiment_parameters/experiment_0.json", &dataset));
  experiments.push_back(new ClassificationAutoencoderExperiment("experiment_parameters/experiment_1.json", &dataset));
  experiments.push_back(new ClassificationAutoencoderExperiment("experiment_parameters/experiment_2.json", &dataset));
  experiments.push_back(new ClassificationAutoencoderExperiment("experiment_parameters/experiment_3.json", &dataset));
  experiments.push_back(new ClassificationAutoencoderExperiment("experiment_parameters/experiment_4.json", &dataset));
  experiments.push_back(new ClassificationAutoencoderExperiment("experiment_parameters/experiment_5.json", &dataset));
  experiments.push_back(new ClassificationAutoencoderExperiment("experiment_parameters/experiment_6.json", &dataset));

  for (unsigned int i = 0; i < experiments.size(); i++)
    experiments[i]->run();

  for (unsigned int i = 0; i < experiments.size(); i++)
    experiments[i]->join();

  printf("program done\n");

  return 0;
}
