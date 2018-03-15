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
    float obstacle_density;
    unsigned int iteration;

    std::string window_label;

  public:
    Arcade(std::string *window_label = nullptr);
    ~Arcade();

    int init();
    void do_action(unsigned int action_id);

    void visualisation();

  private:
    void update_state();

};

#endif
