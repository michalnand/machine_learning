#ifndef _ARENA_H_
#define _ARENA_H_

#include <i_environment.h>
#include <visualisation.h>

#include "tower.h"
#include "attacker.h"

struct sArenaInit
{
  unsigned int width, height;
  unsigned int base_x, base_y;

  unsigned int towers_max_count;
  unsigned int attackers_max_count;
};

class Arena: public IRLEnvironment
{
  protected:
    std::vector<class Tower*>    towers;
    std::vector<class Attacker*> attackers;
    sStateGeometry geometry;
    Visualisation gl_visualisation;

  public:

    Arena();
    ~Arena();

    int init(sArenaInit init_struct);
    void do_action(unsigned int action_id);

    void visualisation();

  private:
    void update_state();

};

#endif
