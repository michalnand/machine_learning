#include <stdio.h>
#include <math_.h>
#include <log.h>
#include <vector>




#include <map.h>
#include <map_grid.h>
#include <map_associative.h>
#include <map_extended.h>

#include <particle_filter.h>

#include "filter_log.h"

#include "qtree.h"

void tree_test()
{
  QTreeNode<int> tree(0, 0.0, 0.0);
  for (unsigned int i = 0; i < (512*512); i++)
  {
    float x = math.rnd();
    float y = math.rnd();
    int value = math.rand()%1000000000;

    //printf("insert [%6.3f %6.3f] = %i\n", x, y, value);

    tree.insert(value, x, y);
  }

//  tree.traverse();

  printf("tree depth %u\n", tree.get_depth());
}

int main()
{
  math.srand(time(NULL));

  /*
  tree_test();

  printf("program done\n");
  return 0;
  */

  unsigned int values_count = 2;
  unsigned int dimensions[2] = {200, 200};

/*
  MapGrid<2, float> map(dimensions);
  map.set_random(values_count);
*/

  MapAssociative<2, float> map(200);
  map.set_random(values_count, dimensions);


  MapExtended map_extended(&map);
  map_extended.save_image("my_map.png", dimensions[0], dimensions[1], true);

  unsigned int particles_count = 8000; // (map.get_items_count()*40)/100;
  ParticleFilter filter(particles_count, &map, 2.0, 0.5);

  FilterLog filter_log(&map, &filter, "./result/");

  //random robot starting position
  std::vector<float> position(map.get_dimension_size());
  for (unsigned int i = 0; i < map.get_dimension_size(); i++)
    position[i] = math.rnd()*map.get_max_dimension(i);

  //default way
  std::vector<float> d_position(map.get_dimension_size());
  for (unsigned int i = 0; i < map.get_dimension_size(); i++)
    d_position[i] = 1.0;

 float p = 0.02;

 for (unsigned int i = 0; i < map.get_dimension_size(); i++)
  printf(">>>>> %f\n", map.get_max_dimension(i));

unsigned int iterations_max = 1000;
for (unsigned int iteration = 0; iteration < iterations_max; iteration++)
{
    for (unsigned int i = 0; i < map.get_dimension_size(); i++)
    {
      if ( (position[i] >= map.get_max_dimension(i)) ||
           (position[i] <= -map.get_max_dimension(i)) ||
           (math.rnd(0, 1) < p) )
        d_position[i]*= -1.0;

      position[i]+= d_position[i];
    }

    void *observation = map.get(&position[0]);
    filter.process(observation, &d_position[0]);

    bool save;
    if ((iteration%10) == 0)
      save = true;
    else
      save = false;

    filter_log.process(iteration, &position[0], filter.result, save);
    printf("done %6.3f %%\n", iteration*100.0/iterations_max);
  }


  printf("program done\n");

  return 0;
}
