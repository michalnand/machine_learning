#include "tiny_net_layer.h"

#include <stdio.h>

void TinyNetLayer::init(unsigned int input_size_, unsigned int output_size_,
                        signed char *weights_, unsigned int weights_scaling_,
                        unsigned char activation_)
{
  input_size      = input_size_;
  output_size     = output_size_;
  weights         = weights_;
  weights_scaling = weights_scaling_;
  activation      = activation_;
}

void TinyNetLayer::process(int *output, int *input)
{
  input[input_size] = TINY_NET_ONE;

  if (activation == EM_LAYER_ACTIVATION_RELU)
    process_relu(output, input);
  else
    process_linear(output, input);
}

void TinyNetLayer::process_linear(int *output, int *input)
{
  unsigned int w_ptr = 0;

  for (unsigned int j = 0; j < output_size; j++)
  {
    long int sum = 0;

    for (unsigned int i = 0; i < (input_size+1); i++)
      sum+= (weights[w_ptr++]*input[i]);

    sum = (sum*weights_scaling)/(127*1000);

    output[j] = sum;
  }
}

void TinyNetLayer::process_relu(int *output, int *input)
{
  unsigned int w_ptr = 0;

  for (unsigned int j = 0; j < output_size; j++)
  {
    long int sum = 0;

    for (unsigned int i = 0; i < (input_size+1); i++)
      sum+= (weights[w_ptr++]*input[i]);

    sum = (sum*weights_scaling)/(127*1000);

    if (sum < 0)
      sum = 0;

    output[j] = sum;
  }

}
