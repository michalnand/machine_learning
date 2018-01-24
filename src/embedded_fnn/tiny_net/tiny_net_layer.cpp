#include "tiny_net_layer.h"

#include "tiny_net_kernel.ck"

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

void TinyNetLayer::process(t_nn_buffer *output, t_nn_buffer *input)
{
  input[input_size] = TINY_NET_ONE;

  matrix_vector_dot_kernel( output, input, weights,
                            input_size, output_size,
                            weights_scaling);

  if (activation == EM_LAYER_ACTIVATION_RELU)
    activation_relu(output);
  else
    activation_linear(output);
}

void TinyNetLayer::activation_linear(t_nn_buffer *output)
{
  (void)output;
}

void TinyNetLayer::activation_relu(t_nn_buffer *output)
{
  for (unsigned int j = 0; j < output_size; j++)
  {
    int tmp = output[j];
    if (tmp < 0)
      tmp = 0;

    output[j] = tmp;
  }
}
