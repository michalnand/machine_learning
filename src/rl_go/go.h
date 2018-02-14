#ifndef _GO_H_
#define _GO_H_

#include <i_environment.h>
#include <visualisation.h>

#define GO_PLAYER_BLACK ((unsigned int)0)
#define GO_PLAYER_WHITE ((unsigned int)1)

struct sBoardItem
{
  int stone;
  int liberty;
};

class GO: public IRLEnvironment
{
  protected:

    std::vector<std::vector<sBoardItem>> board;

    unsigned int board_size;
    unsigned int active_player;

    int black_player_score, white_player_score;

  public:
    GO(unsigned int board_size = 19);
    ~GO();

    int init(unsigned int board_size);
    void do_action(unsigned int action_id);

    void visualisation();
    void set_active_player(unsigned int active_player);
    void set_random();
  private:

    void update_state();
    void update_liberty_count();

    int empty_field_liberty(int j, int i);
    int stone_field_liberty(int j, int i);
    int max(int a, int b);

    void capture_stones();

    void update_score();
    void play_on_field(unsigned int action_id);
    void update_availible_moves();
};

#endif
