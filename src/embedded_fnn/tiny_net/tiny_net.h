#ifndef _TINY_NET_H_
#define _TINY_NET_H_

#include "tiny_net_layer.h"

class TinyNet
{
  public:
    int *input;
    int *output;

    void init();
    void process();

    unsigned int get_input_size();
    unsigned int get_output_size();

  private:
    void buffer_start();
    void buffer_exchange();
};

extern TinyNet nn;

#endif
