#ifndef _TINY_NET_LAYER_H_
#define _TINY_NET_LAYER_H_

#define EM_LAYER_ACTIVATION_LINEAR    0
#define EM_LAYER_ACTIVATION_RELU      1

#define TINY_NET_ONE          ((int)127)

class TinyNetLayer
{
  private:
    unsigned int input_size;
    unsigned int output_size;

    signed char *weights;
    unsigned int  weights_scaling;

    unsigned char activation;

  public:
    void init(unsigned int input_size_, unsigned int output_size_,
              signed char *weights_, unsigned int weights_scaling_,
              unsigned char activation_);

    void process(int *output, int *input);

  private:
    void process_linear(int *output, int *input);
    void process_relu(int *output, int *input);
};

#endif
