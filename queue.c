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
  struct queue *q = malloc(sizeof(struct queue));
  struct queue *qToCheck = malloc(sizeof(struct queue));

  if (q == NULL || qToCheck == NULL)
  {
    return -1;
  }

  (q->data).head = NULL;
  (qToCheck->data).head = NULL;

  enqueue(q, start);
  enqueue(qToCheck, start);
  int numStepNow = 0;
  while ((q->data).head != NULL)
  {
    struct game_state currentState = dequeue(q);
    numStepNow = currentState.num_steps;
    currentState.num_steps = 0;
    uint64_t serializedCurrent = serialize(currentState);
    currentState.num_steps = numStepNow;
    if (completedGame(currentState))
    {
      free_list(q->data);
      free_list(qToCheck->data);
      return numStepNow;
    }
    else
    {
      struct game_state nextState = currentState;
      int isRepeated = 0;
      
      struct list_node* qChecker = qToCheck->data.head;
      while (qChecker->next != NULL)
      {
        qChecker = qChecker->next;
        if (qChecker->value == serializedCurrent) 
        {
          isRepeated = 1;
          break;
        }
        
      }

      if (isRepeated == 0)
      {
        if (nextState.empty_row != 3)
        {
          move_up(&nextState);
          enqueue(q, nextState);
          nextState = currentState;
        }
        if (nextState.empty_row != 0)
        {
          move_down(&nextState);
          enqueue(q, nextState);
          nextState = currentState;
        }
        if (nextState.empty_col != 3)
        {
          move_left(&nextState);
          enqueue(q, nextState);
          nextState = currentState;
        }
        if (nextState.empty_col != 0)
        {
          move_down(&nextState);
          enqueue(q, nextState);
          nextState = currentState;
        }
        currentState.num_steps = 0;
        enqueue(qToCheck, currentState);
      }
    }
  }
    free_list(q->data);
    free_list(qToCheck->data);
  return numStepNow;
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
