#ifndef _FILTER_LOG_H_
#define _FILTER_LOG_H_

#include <map.h>
#include <particle_filter.h>

#include <string>
#include <vector>
#include <image.h>


struct sFilterLogPoint
{
  std::vector<float> point;
};


class FilterLog
{
  protected:
    Map *m_map;
    ParticleFilter *m_filter;

    std::string m_file_name_prefix;

    float m_range_x, m_range_y;

  private:
    unsigned int m_width, m_height;

    std::vector<sFilterLogPoint> real_path, filtered_path;


  public:
    FilterLog(Map *map, ParticleFilter *filter,
              std::string file_name_prefix);

    ~FilterLog();

    void process(unsigned int iteration,
                 float *position,
                 float *filter_position,
                 bool save);

  private:
    void add_map(CImage &image);
    void add_particles(CImage &image);

    unsigned int x_to_image_x(float input);
    unsigned int y_to_image_y(float input);

    void add_path(CImage &image, std::vector<sFilterLogPoint> path, float r, float g, float b);
    void paint_square(CImage &image, unsigned int x, unsigned int y, unsigned int size,
                      float r, float g, float b);
};

#endif
