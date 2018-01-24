
void matrix_vector_dot_kernel(t_nn_buffer *output, t_nn_buffer *input, signed char *weights,
                              unsigned int input_size, unsigned int output_size,
                              unsigned int weights_scaling)
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
