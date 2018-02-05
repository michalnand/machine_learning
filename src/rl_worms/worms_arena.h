#ifndef _WORMS_ARENA_H_
#define _WORMS_ARENA_H_

#include <i_environment.h>
#include <visualisation.h>

#include <food.h>
#include <worm.h>

class WormsArena: public IRLEnvironment
{
  protected:
    unsigned int iteration;
    float x, y;
    float dx, dy;
    
    sStateGeometry geometry;

    Visualisation gl_visualisation;
    Food food;
    Worm worm;

  public:
    WormsArena();
    ~WormsArena();

    int init();
    void do_action(unsigned int action_id);

    void visualisation();
    void log();

  private:
    void update_state();
};

#endif
