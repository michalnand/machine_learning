#include "go.h"

GO::GO()
{
  board_size = 19;

  for (unsigned int j = 0; j < board_size; j++)
  {
    std::vector<float> tmp;
    for (unsigned int i = 0; i < board_size; i++)
      tmp.push_back(0.0);

    board.push_back(tmp);
  }
}

GO::~GO()
{

}

int GO::init()
{
  board_size = 19;

  for (unsigned int j = 0; j < board_size; j++)
  {
    std::vector<float> tmp;
    for (unsigned int i = 0; i < board_size; i++)
      tmp.push_back(0.0);

    board.push_back(tmp);
  }

  actions_count = board_size*board_size;

  state.geometry.w = board_size;
  state.geometry.h = board_size;
  state.geometry.d = 1;

  availible_actions_init();

  return 0;
}

void GO::do_action(unsigned int action_id)
{
  if (availible_actions[action_id] != false)
    return;
}

void GO::visualisation()
{
  for (unsigned int j = 0; j < board_size; j++)
  {
    for (unsigned int i = 0; i < board_size; i++)
    {
      float v = board[j][i];
      if (v > 0.9)
        printf("B");
      else
      if (v < -0.9)
        printf("W");
      else
        printf(".");

      printf(" ");
    }
    
    printf("\n");
  }
}


void GO::update_state()
{

}
