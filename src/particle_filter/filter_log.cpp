#include "filter_log.h"
#include <math_.h>


#include <image.h>
#include <iostream>
#include <sstream>
#include <iomanip>

FilterLog::FilterLog  (Map *map, ParticleFilter *filter,
                       std::string file_name_prefix)
{
  m_map = map;
  m_filter = filter;
  m_file_name_prefix = file_name_prefix;

  m_width = 500;
  m_height = 500;

  m_range_x = m_map->get_max_dimension(0);
  m_range_y = m_map->get_max_dimension(1);
}

FilterLog::~FilterLog()
{

}

void FilterLog::process( unsigned int iteration,
                         float *position,
                         float *filter_position,
                         bool save)
{
  sFilterLogPoint tmp;
  tmp.point.resize(m_map->get_dimension_size());

  for (unsigned int i = 0; i < m_map->get_dimension_size(); i++)
    tmp.point[i] = position[i];
  real_path.push_back(tmp);

  for (unsigned int i = 0; i < m_map->get_dimension_size(); i++)
    tmp.point[i] = filter_position[i];
  filtered_path.push_back(tmp);

  if (save == true)
  {
    CImage result_image(m_width, m_height);

    add_map(result_image);

    add_particles(result_image);
    add_path(result_image, real_path, 0.0, 1.0, 0.0);
    add_path(result_image, filtered_path, 1.0, 0.0, 0.0);

    std::stringstream s_iteration;
    s_iteration << std::setw(5) << std::setfill('0') << iteration;
    std::string image_file_name = m_file_name_prefix+s_iteration.str()+".png";
    result_image.save(image_file_name);
  }
}


void FilterLog::add_map(CImage &image)
{
  std::vector<float> position;
  position.resize(m_map->get_dimension_size());

  for (float y = -m_range_y; y < m_range_y; y+= 0.25)
    for (float x = -m_range_x; x < m_range_x; x+= 0.25)
    {
      position[0] = x;
      position[1] = y;

      void *value_tmp = m_map->get(&position[0]);

      unsigned int x_ = x_to_image_x(x);
      unsigned int y_ = y_to_image_y(y);

      float value = *((float*)value_tmp);

      if (value < 0.0)
        value = 0.0;
      if (value > 1.0)
        value = 1.0;

      image.pixels[y_][x_].b[0] = value;
      image.pixels[y_][x_].b[1] = value;
      image.pixels[y_][x_].b[2] = value;
    }
}


void FilterLog::add_particles(CImage &image)
{
  for (unsigned int i = 0; i < m_filter->get_particles_count(); i++)
  {
    sParticle *particle = m_filter->get_particle(i);

    unsigned int x = x_to_image_x(particle->position[0]);
    unsigned int y = y_to_image_y(particle->position[1]);


    image.pixels[y][x].b[0] = 1.0;
    image.pixels[y][x].b[1] = 0.0;
    image.pixels[y][x].b[2] = 1.0;
  }
}

unsigned int FilterLog::x_to_image_x(float input)
{
  unsigned int result = math.map(input, -m_range_x, m_range_x, 0, m_width-1);

  if (result >= (m_width-1))
    result = m_width-1;

  return result;
}

unsigned int FilterLog::y_to_image_y(float input)
{
  unsigned int result = math.map(input, -m_range_y, m_range_y, 0, m_height-1);

  if (result >= (m_height-1))
    result = m_height-1;

  return result;
}

void FilterLog::add_path(CImage &image, std::vector<sFilterLogPoint> path, float r, float g, float b)
{
  for (unsigned int i = 0; i < path.size(); i++)
  {
    unsigned int x = x_to_image_x(path[i].point[0]);
    unsigned int y = y_to_image_y(path[i].point[1]);

    image.pixels[y][x].b[0] = r;
    image.pixels[y][x].b[1] = g;
    image.pixels[y][x].b[2] = b;
  }

  unsigned int last = path.size()-1;
  unsigned int x = x_to_image_x(path[last].point[0]);
  unsigned int y = y_to_image_y(path[last].point[1]);

  paint_square(image, x, y, 10, r, g, b);
}


void FilterLog::paint_square(CImage &image, unsigned int x, unsigned int y, unsigned int size,
                            float r, float g, float b)
{
  for (unsigned int j = 0; j < size; j++)
  for (unsigned int i = 0; i < size; i++)
  {
    unsigned int y_ = (j + y) - size/2;
    unsigned int x_ = (i + x) - size/2;

    if (y_ > (m_width-1))
      y_ = m_width-1;

    if (x_ > (m_height-1))
      x_ = m_height-1;

    image.pixels[y_][x_].b[0] = r;
    image.pixels[y_][x_].b[1] = g;
    image.pixels[y_][x_].b[2] = b;
  }
}
