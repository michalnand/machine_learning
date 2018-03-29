#ifndef _STACK_GAME_H_
#define _STACK_GAME_H_

#include "stack_item.h"
#include <visualisation.h>

class StackGame
{
  private:
    std::vector<StackItem*> items;

    unsigned int width, height;
    unsigned int item_width, item_height;

    Visualisation visualisation;

    float overlap, overlap_filtered;

  public:
    StackGame(unsigned int width,
          unsigned int height);

    ~StackGame();

    void action(unsigned int action_id);
    void main();
    float get_overlap();

  private:
    void draw();
    void draw_item(unsigned int idx);

    bool game_over();
    bool make_smaller();

    void init();
};

#endif
