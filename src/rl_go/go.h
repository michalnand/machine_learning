#ifndef _GO_H_
#define _GO_H_

#include <i_environment.h>
#include <visualisation.h>


class GO: public IRLEnvironment
{
  protected:
    unsigned int board_size;
    std::vector<std::vector<float>> board;

  public:
    GO();
    ~GO();

    int init();
    void do_action(unsigned int action_id);

    void visualisation();

  private:
    void update_state();
};

#endif
