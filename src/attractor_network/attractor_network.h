#ifndef _ATTRACTOR_NETWORK_H_
#define _ATTRACTOR_NETWORK_H_

#define AN_DETECTION_THRESHOLD    ((float)0.95)

template<class t_value> struct ANItem
{
  float w;
  t_value value;
};


template<class t_value> class AttractorNetwork
{
  protected:
    ANItem<t_value> *neurons;

    unsigned int m_neurons_count, m_neuron_ptr;
    float lambda;

  public:

    AttractorNetwork()
    {
      neurons         = nullptr;
      m_neurons_count = 0;
      m_neuron_ptr    = 0;
    }

    ~AttractorNetwork()
    {
      if (neurons != nullptr)
      {
        delete neurons;

        neurons         = nullptr;
        m_neurons_count = 0;
        m_neuron_ptr    = 0;
      }
    }

    int init(unsigned int neurons_count, float distance_threshold)
    {
      float p = AN_DETECTION_THRESHOLD;
      lambda  = p/(1.0 - p);
      lambda  = lambda*distance_threshold*distance_threshold;

      m_neurons_count = neurons_count;
      m_neuron_ptr    = 0;
      neurons         = new ANItem<t_value>[m_neurons_count];

      return 0;
    }

    int add(t_value &value)
    {
      if (m_neuron_ptr == 0)
      {
        neurons[m_neuron_ptr] = value;
        m_neuron_ptr++;
        return 0;
      }

      if (m_neuron_ptr < m_neurons_count)
      {
        int idx = find_nearest(value);
        m_neuron_ptr++;
        return 0;
      }

      return -1;
    }

  private:

    int find_nearest(t_value &value)
    {
      if (m_neuron_ptr == 0)
        return -1;

      return bisection(value.position);
    }

    unsigned int bisection(float position)
    {
      unsigned int a = 0;
      unsigned int b = 0;

      if (m_neurons_count > 0)
        b = m_neurons_count - 1;

      unsigned int center = 0;
      while (a < b)
      {
        center = (a+b)/2;
        if (neurons[center].w < position)
          b = center;
        else
          a = center;
      }

      return center;
    }

    float likelihood_func(float value_a, float value_b)
    {
      float tmp = value_a - value_b;
      return lambda/(lambda + tmp*tmp);
    }
};



/*
template<class t_value> class AttractorNetwork
{
  protected:
    ANItem<t_value> *neurons;

    unsigned int m_items_count, m_item_ptr;
    float distance_threshold, k;

  public:

    MapLine()
    {
      m_items_count = 0;
      m_item_ptr = 0;

      m_items = nullptr;

      k = 1.0;
    }

    virtual ~MapLine()
    {
      if (m_items != nullptr)
      {
        delete m_items;
        m_items = nullptr;
      }
    }

    void init(unsigned int items_count, float distance_threshold_, bool load_map)
    {
      if (m_items == nullptr)
      {
        m_items_count = items_count;

        distance_threshold = distance_threshold_;

        float p = MAP_DETECTION_THRESHOLD;
        k = p/(1.0 - p);
        k= k*distance_threshold*distance_threshold;

        m_items = new MapLineItem<t_map_value>[m_items_count];
      }

      if (load_map)
      {
        for (unsigned int i = 0; i < m_items_count; i++)
        {
          MapLineItem<t_map_value> tmp;
          int read_res  = stream.read(&tmp);
          if (read_res == 0)
            m_items[i] = tmp;
          else
          {
            m_items_count = i;
            m_item_ptr    = i;
            break;
          }
        }
      }
      else
      {
        stream.format();
      }

      stream.rewind();
    }


      unsigned int bisection(float position)
      {
        unsigned int a = 0;
        unsigned int b = 0;

        if (m_items_count > 0)
          b = m_items_count - 1;

        unsigned int center = 0;
        while (a < b)
        {
          center = (a+b)/2;
          if (m_items[center].position < position)
            b = center;
          else
            a = center;
        }

        return center;
      }

      float likelihood_func(float x, float map_x)
      {
        float tmp = map_x - x;
        return k/(k + tmp*tmp);
      }
};
*/

#endif
