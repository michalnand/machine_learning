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

  matrix_dot(output, input);

  if (activation == EM_LAYER_ACTIVATION_RELU)
    activation_relu(output);
  else
    activation_linear(output);
}

void TinyNetLayer::matrix_dot(int *output, int *input)
{
  unsigned int w_ptr = 0;

  for (unsigned int j = 0; j < output_size; j++)
  {
    unsigned int input_ptr  = 0;
    unsigned int size       = input_size+1;

    long int sum = 0;


    while (size >= 4)
    {
      sum+= (weights[w_ptr]*input[input_ptr]); w_ptr++; input_ptr++;
      sum+= (weights[w_ptr]*input[input_ptr]); w_ptr++; input_ptr++;
      sum+= (weights[w_ptr]*input[input_ptr]); w_ptr++; input_ptr++;
      sum+= (weights[w_ptr]*input[input_ptr]); w_ptr++; input_ptr++;

      size-= 4;
    }


    while (size)
    {
      sum+= (weights[w_ptr]*input[input_ptr]); w_ptr++; input_ptr++;
      size--;
    }

    sum = (sum*weights_scaling)/(127*1000);
    output[j] = sum;
  }
}

void TinyNetLayer::activation_linear(int *output)
{
  (void)output;
}

void TinyNetLayer::activation_relu(int *output)
{
  for (unsigned int j = 0; j < output_size; j++)
  {
    int tmp = output[j];
    if (tmp < 0)
      tmp = 0;

    output[j] = tmp;
  }
}
