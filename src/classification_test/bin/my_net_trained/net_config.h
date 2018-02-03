#ifndef __NET_CONFIG_H_
#define __NET_CONFIG_H_



#include "tiny_net_layer.h"
#include "layer_1_int.h"
#include "layer_2_int.h"



#define TINY_NET_LAYERS_COUNT    ((unsigned int)2)



TinyNetLayer tiny_net_layers[TINY_NET_LAYERS_COUNT];



unsigned int tiny_net_weights_scaling[TINY_NET_LAYERS_COUNT] = {390, 939, };


signed char* tiny_net_weights_init[TINY_NET_LAYERS_COUNT] = {weights_layer_1, weights_layer_2, };


unsigned int tiny_net_topology[TINY_NET_LAYERS_COUNT+1] ={81, 256, 10};


#define TINY_NET_BUFFER_SIZE    ((unsigned int)257)



#endif
