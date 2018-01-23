#include "tiny_net.h"

#include "net_config.h"

#include <stdio.h>

TinyNet nn;

t_nn_buffer tiny_net_buffer_a[TINY_NET_BUFFER_SIZE];
t_nn_buffer tiny_net_buffer_b[TINY_NET_BUFFER_SIZE];

void TinyNet::init()
{
  buffer_start();

  for (unsigned int i = 0; i < TINY_NET_BUFFER_SIZE; i++)
  {
    input[i]  = 0;
    output[i] = 0;
  }

  for (unsigned int i = 0; i < TINY_NET_LAYERS_COUNT; i++)
  {
    unsigned char activation = EM_LAYER_ACTIVATION_RELU;

    if ((i+1) == TINY_NET_LAYERS_COUNT)
      activation = EM_LAYER_ACTIVATION_LINEAR;

    tiny_net_layers[i].init(tiny_net_topology[i], tiny_net_topology[i+1],
                            tiny_net_weights_init[i], tiny_net_weights_scaling[i],
                            activation);
  }
}

void TinyNet::process()
{
  buffer_start();

  for (unsigned int i = 0; i < TINY_NET_LAYERS_COUNT; i++)
  {
    tiny_net_layers[i].process(output, input);
    buffer_exchange();
  }

  buffer_exchange();
}

unsigned int TinyNet::get_input_size()
{
  return tiny_net_topology[0];
}

unsigned int TinyNet::get_output_size()
{
  return tiny_net_topology[TINY_NET_LAYERS_COUNT];
}

void TinyNet::buffer_start()
{
  input   = tiny_net_buffer_a;
  output  = tiny_net_buffer_b;
}

void TinyNet::buffer_exchange()
{
  t_nn_buffer *tmp;
  tmp = input;
  input = output;
  output = tmp;
}
