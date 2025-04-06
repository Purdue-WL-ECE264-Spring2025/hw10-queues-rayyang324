#include "queue.h"
#include "tile_game.h"
#include <stdlib.h>

bool completedGame(struct game_state);

void enqueue(struct queue *q, struct game_state state)
{
  uint64_t serializedState = serialize(state);
  insert_at_tail(&q->data, (size_t)serializedState);
  return;
}

struct game_state dequeue(struct queue *q)
{
  struct game_state removedGameState = deserialize((remove_from_head(&q->data)));
  return removedGameState;
}

int number_of_moves(struct game_state start)
{
  // have a q of possible movements and a qToCheck for checking duplication
  struct queue *q = malloc(sizeof(struct queue));
  struct queue *qToCheck = malloc(sizeof(struct queue));

  // finding completed state serial number
  struct game_state completedState = {.tiles = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 0}},
    .empty_row = 3, .empty_col = 3, .num_steps = 0};
  uint64_t serializedComplete = serialize(completedState);

  if (q == NULL || qToCheck == NULL)
  {
    return -1;
  }

  (q->data).head = NULL;
  (qToCheck->data).head = NULL;
  // queue the start
  enqueue(q, start);
  enqueue(qToCheck, start);

  // steps made
  int numStepNow;

  while ((q->data).head != NULL)
  {
    struct game_state currentState = dequeue(q);
    numStepNow = currentState.num_steps;
    currentState.num_steps = 0;
    uint64_t serializedCurrent = serialize(currentState);
    currentState.num_steps = numStepNow;
    if (serializedCurrent == serializedComplete)
    {
      free_list(q->data);
      free_list(qToCheck->data);
      free(q);
      free(qToCheck);
      return numStepNow;
    }
    else
    {
      struct game_state nextState = currentState;
      int isRepeated = 0;
      
      struct list_node* qChecker = qToCheck->data.head;
      while (qChecker->next != NULL)
      {
        if (qChecker->value == serializedCurrent) 
        {
          isRepeated = 1;
          break;
        }
        qChecker = qChecker->next;
      }
      if (isRepeated == 0)
      {
        if (currentState.empty_row != 3)
        {
          nextState = currentState;
          move_up(&nextState);
          enqueue(q, nextState);
        }
        if (currentState.empty_row != 0)
        {
          nextState = currentState;
          move_down(&nextState);
          enqueue(q, nextState);
        }
        if (currentState.empty_col != 3)
        {
          nextState = currentState;
          move_left(&nextState);
          enqueue(q, nextState);
        }
        if (currentState.empty_col != 0)
        {
          nextState = currentState;
          move_right(&nextState);
          enqueue(q, nextState);
        }
        currentState.num_steps = 0;
        enqueue(qToCheck, currentState);

      }
    }
  }
    free_list(q->data);
    free_list(qToCheck->data);
    free(q);
    free(qToCheck);
  return 0;
}


  bool completedGame(struct game_state state)
  {
    int correctness = 0; // check if the state of the game is at the end or not
    for (int i = 0; i < 4; i++)
    {
      for (int j = 0; j < 4; j++)
      {
        if (state.tiles[i][j] == 4 * i + j + 1 || (state.tiles[state.empty_row][state.empty_col] == 0 && state.empty_row == i && state.empty_col == j))
        {
          correctness++;
        }
      }
    }
    return ((correctness == 16) ? true : false);
  }
