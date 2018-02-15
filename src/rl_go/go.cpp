#include "go.h"

#define GO_EMPTY_STONE    ((int)0)
#define GO_BLACK_STONE    ((int)1)
#define GO_WHITE_STONE    ((int)-1)

GO::GO(unsigned int board_size)
{
  init(board_size);
}

GO::~GO()
{

}

int GO::init(unsigned int board_size)
{
  this->board_size = board_size;

  board.resize(board_size);
  for (unsigned int j = 0; j < board_size; j++)
  {
    board[j].resize(board_size);

    for (unsigned int i = 0; i < board_size; i++)
    {
      board[j][i].stone = GO_EMPTY_STONE;
      board[j][i].liberty = 0;
    }
  }

  actions_count = board_size*board_size + 1; //+1 for pass

  state.geometry.w = board_size;
  state.geometry.h = board_size;
  state.geometry.d = 1;

  availible_actions_init();

  this->active_player = GO_PLAYER_BLACK;

  black_player_score = 0;
  white_player_score = 0;

  return 0;
}

void GO::do_action(unsigned int action_id)
{
  if (availible_actions[action_id] != true) //illegal move
    return;

  if (action_id == (availible_actions.size()-1))  //PASS action, no state change
    return;

  int j = action_id/board_size;
  int i = action_id%board_size;
  play_on_field(j, i);

  update_liberty_count();   //compute liberty count
  capture_stones();         //capture oponent stones

  update_score();           //count score
}

void GO::visualisation()
{
  printf("stones :\n");
  for (unsigned int j = 0; j < board_size; j++)
  {
    for (unsigned int i = 0; i < board_size; i++)
    {
      auto v = board[j][i].stone;
      if (v == GO_BLACK_STONE)
        printf("B");
      else
      if (v == GO_WHITE_STONE)
        printf("W");
      else
        printf(".");

      printf(" ");
    }

    printf("\n");
  }

  printf("liberty :\n");

  for (unsigned int j = 0; j < board_size; j++)
  {
    for (unsigned int i = 0; i < board_size; i++)
    {
      auto v = board[j][i].liberty;
      printf("%4i ", v);
    }

    printf("\n");
  }

  printf("\nscore %i %i\n", black_player_score, white_player_score);
  printf("\n\n\n");


  //TODO paint nice board in opengl
}

void GO::set_active_player(unsigned int active_player)
{
  this->active_player = active_player;

  update_availible_moves();
}

void GO::set_random()
{
  for (unsigned int j = 0; j < board_size; j++)
    for (unsigned int i = 0; i < board_size; i++)
    {
      switch (rand()%4)
      {
        case 0: board[j][i].stone = GO_BLACK_STONE; break;
        case 1: board[j][i].stone = GO_WHITE_STONE; break;
        default: board[j][i].stone = 0; break;

      }
    }
}

void GO::update_state()
{

}

void GO::update_liberty_count()
{
  for (unsigned int j = 0; j < board_size; j++)
    for (unsigned int i = 0; i < board_size; i++)
      board[j][i].liberty = 0;

  bool change = true;
  while (change == true)
  {
    change = false;

    for (unsigned int j = 0; j < board_size; j++)
      for (unsigned int i = 0; i < board_size; i++)
        if (board[j][i].stone != GO_EMPTY_STONE)
        {
          int empty_liberty = empty_field_liberty(j, i);
          int stone_liberty = stone_field_liberty(j, i);

          int result = max(empty_liberty, stone_liberty);

          if (board[j][i].liberty != result)
          {
            board[j][i].liberty = result;
            change = true;
          }
        }
    }
}

int GO::count_black_captured_stones()
{
  int result = 0;
  for (unsigned int j = 0; j < board_size; j++)
    for (unsigned int i = 0; i < board_size; i++)
      if (board[j][i].stone == GO_BLACK_STONE)
      if (board[j][i].liberty == 0)
        result++;
  return result;
}

int GO::count_white_captured_stones()
{
  int result = 0;
  for (unsigned int j = 0; j < board_size; j++)
    for (unsigned int i = 0; i < board_size; i++)
      if (board[j][i].stone == GO_WHITE_STONE)
      if (board[j][i].liberty == 0)
        result++;
  return result;
}


int GO::empty_field_liberty(int j, int i)
{
  int result = 0;

  if ((i+1) < (int)board_size)
  {
    if (board[j][i+1].stone == GO_EMPTY_STONE)
      result++;
  }

  if ((i-1) >= 0)
  {
    if (board[j][i-1].stone == GO_EMPTY_STONE)
      result++;
  }

  if ((j+1) < (int)board_size)
  {
    if (board[j+1][i].stone == GO_EMPTY_STONE)
      result++;
  }

  if ((j-1) >= 0)
  {
    if (board[j-1][i].stone == GO_EMPTY_STONE)
      result++;
  }

  return result;
}




int GO::stone_field_liberty(int j, int i)
{
  int result = 0;
  int stone = board[j][i].stone;

  if ((i+1) < (int)board_size)
  {
    if (board[j][i+1].stone == stone)
      result = max(result, board[j][i+1].liberty);
  }

  if ((i-1) >= 0)
  {
    if (board[j][i-1].stone == stone)
      result = max(result, board[j][i-1].liberty);
  }

  if ((j+1) < (int)board_size)
  {
    if (board[j+1][i].stone == stone)
      result = max(result, board[j+1][i].liberty);
  }

  if ((j-1) >= 0)
  {
    if (board[j-1][i].stone == stone)
      result = max(result, board[j-1][i].liberty);
  }

  return result;
}




void GO::capture_stones()
{
  if (active_player == GO_PLAYER_BLACK)
  {
    for (unsigned int j = 0; j < board_size; j++)
      for (unsigned int i = 0; i < board_size; i++)
      {
        if (board[j][i].stone == GO_WHITE_STONE)
        if (board[j][i].liberty == 0)
          board[j][i].stone = GO_EMPTY_STONE;
      }
  }


  if (active_player == GO_PLAYER_WHITE)
  {
    for (unsigned int j = 0; j < board_size; j++)
      for (unsigned int i = 0; i < board_size; i++)
      {
        if (board[j][i].stone == GO_BLACK_STONE)
        if (board[j][i].liberty == 0)
          board[j][i].stone = GO_EMPTY_STONE;
      }
  }

}

void GO::update_score()
{
  black_player_score = 0;
  white_player_score = 0;

  for (unsigned int j = 0; j < board_size; j++)
    for (unsigned int i = 0; i < board_size; i++)
    {
      if (board[j][i].stone == GO_BLACK_STONE)
        black_player_score++;
      if (board[j][i].stone == GO_WHITE_STONE)
        white_player_score++;
    }
}



void GO::update_availible_moves()
{
  //play only on empty fields
  for (unsigned int j = 0; j < board_size; j++)
    for (unsigned int i = 0; i < board_size; i++)
    {
      int idx = position_to_action(j, i);
      if (board[j][i].stone == GO_EMPTY_STONE)
          availible_actions[idx] = true;
      else
        availible_actions[idx] = false;
    }

  //avoid suicide
  for (unsigned int j = 0; j < board_size; j++)
    for (unsigned int i = 0; i < board_size; i++)
      if (board[j][i].stone == GO_EMPTY_STONE)
      {
        //try to play
        play_on_field(j, i);

        update_liberty_count();

        //and check for suicide
        int black_captured = count_black_captured_stones();
        int white_captured = count_white_captured_stones();

        if (active_player == GO_PLAYER_BLACK)
        {
          if (white_captured > 0)
            availible_actions[position_to_action(j, i)] = true;
          else
          if (black_captured == 0)
            availible_actions[position_to_action(j, i)] = true;
        }

        if (active_player == GO_PLAYER_WHITE)
        {
          if (black_captured > 0)
            availible_actions[position_to_action(j, i)] = true;
          else
          if (white_captured == 0)
            availible_actions[position_to_action(j, i)] = true;
        }

        //restore previous state
        unplay_on_field(j, i);
      }

}

int GO::position_to_action(int j, int i)
{
  return j*board_size + i;
}

void GO::play_on_field(int j, int i)
{


  if (active_player == GO_PLAYER_BLACK)
    board[j][i].stone = GO_BLACK_STONE;

  if (active_player == GO_PLAYER_WHITE)
    board[j][i].stone = GO_WHITE_STONE;
}

void GO::unplay_on_field(int j, int i)
{

  if (active_player == GO_PLAYER_BLACK)
    board[j][i].stone = GO_EMPTY_STONE;

  if (active_player == GO_PLAYER_WHITE)
    board[j][i].stone = GO_EMPTY_STONE;
}

int GO::max(int a, int b)
{
  if (a > b)
    return a;
  return b;
}
