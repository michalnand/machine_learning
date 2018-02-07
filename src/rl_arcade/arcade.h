#ifndef _ARCADE_H_
#define _ARCADE_H_

#include <i_environment.h>
#include <visualisation.h>


class Arcade: public IRLEnvironment
{
  protected:
    unsigned int x, y, move_state;
    std::vector<std::vector<float>> screen;

    sStateGeometry geometry;

    Visualisation gl_visualisation;

    unsigned int iteration;
    float score_filtered;
    float obstacle_density;
  public:
    Arcade();
    ~Arcade();

    int init();
    void do_action(unsigned int action_id);

    void visualisation();

  private:
    void update_state();

};

#endif