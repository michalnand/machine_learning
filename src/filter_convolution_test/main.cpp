#include <image.h>
#include <input_layer.h>
#include <output_layer.h>
#include <filter_layer.h>

#include <timer.h>

#include <math_.h>

void convolution_test(float *output, float *input,
                      float *weights,
                      sLayerGeometry input_geometry, sLayerGeometry kernel_geometry)
{
  float *dev_input  = nn_allocator.allocate(input_geometry.w*input_geometry.h*input_geometry.d);
  float *dev_output = nn_allocator.allocate(input_geometry.w*input_geometry.h*kernel_geometry.d);

  sHyperparameters hyperparameters;

  InputLayer input_layer;
  OutputLayer output_layer;
  FilterLayer filter;

  sLayerGeometry output_geometry = input_geometry;
  output_geometry.d = kernel_geometry.d;

  input_layer.init(input_geometry, kernel_geometry, hyperparameters);
  output_layer.init(output_geometry, kernel_geometry, hyperparameters);
  filter.init(input_geometry, kernel_geometry, hyperparameters);
  filter.load_weights(weights);

  input_layer.forward(dev_input, input);

  timer.start();

  filter.forward(&dev_output[0], &dev_input[0]);

  timer.stop();

  output_layer.forward(output, &dev_output[0]);

  printf("computing time %6.3f[ms]\n", timer.get_duration());

  nn_allocator.free(dev_input);
  nn_allocator.free(dev_output);
}

int main()
{
  math.srand(time(NULL));

  CImage input_image("input_big.jpg");

  sLayerGeometry input_geometry;
  input_geometry.w = input_image.width;
  input_geometry.h = input_image.height;
  input_geometry.d = 3;

  sLayerGeometry kernel_geometry;
  kernel_geometry.w = 3;
  kernel_geometry.h = 3;
  kernel_geometry.d = 5;


  float weights[] = {
                        0.0,   0.0,   0.0,  0.0,  0.0,  0.0,   0.0,   0.0,   0.0,
                       -0.5,  -0.5,  -0.5,   1.0,   1.0,   1.0,  -0.5,  -0.5,  -0.5,
                       0.0,   0.0,   0.0,  0.0,  0.0,  0.0,   0.0,   0.0,   0.0,

                       0.0,   0.0,   0.0,  -0.5,  -0.5,  -0.5,   0.0,   0.0,   0.0,
                      0.0,  0.0,  0.0,   1.0,   1.0,   1.0,  0.0,  0.0,  0.0,
                      0.0,   0.0,   0.0,  -0.5,  -0.5,  -0.5,   0.0,   0.0,   0.0,

                      0.037, 0.037, 0.037, 0.037, 0.037, 0.037, 0.037, 0.037, 0.037,
                      0.037, 0.037, 0.037, 0.037, 0.037, 0.037, 0.037, 0.037, 0.037,
                      0.037, 0.037, 0.037, 0.037, 0.037, 0.037, 0.037, 0.037, 0.037,

                      0.0,   0.0,   0.0,  -0.083,  -0.083,  -0.083,   0.0,   0.0,   0.0,
                     -0.083,  -0.083,  -0.083,   0.333,   0.333,   0.333,  -0.083,  -0.083,  -0.083,
                      0.0,   0.0,   0.0,  -0.083,  -0.083,  -0.083,   0.0,   0.0,   0.0,

                        0.0,   0.0,   0.0,  -0.066,  -0.066,  -0.066,   0.0,   0.0,   0.0,
                       -0.066,  -0.066,  -0.066,   0.333,   0.333,   0.333,  -0.066,  -0.066,  -0.066,
                        0.0,   0.0,   0.0,  -0.066,  -0.066,  -0.066,   0.0,   0.0,   0.0,
                    };


  unsigned int output_size = input_geometry.w*input_geometry.h*kernel_geometry.d;
  std::vector<float> input = input_image.as_vector(false);

  std::vector<float> output(output_size);

  printf("output size %u %u\n", output_size, kernel_geometry.d);

  for (unsigned int i =0 ; i < 10000; i++)
  convolution_test(&output[0], &input[0], weights, input_geometry, kernel_geometry);


  CImage output_image(input_geometry.w, input_geometry.h*kernel_geometry.d);

  output_image.from_feature_map(output, kernel_geometry.d);
  output_image.save("output.jpg");


  printf("program done\n");
  return 0;
}
