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
/*
node bfs(graph g, node start, node search) {
  queue q = new_queue();
  while (!empty(stack)) {
      node cur = dequeue(&q);
      if (equals(cur, search))
      {
        return cur;
      }
      else
      {
        for (node child in children(cur))
        {
            enqueue(&q, child);
        }
      }
  }
}
*/
int number_of_moves(struct game_state start)
{
  struct queue *q = malloc(sizeof(struct queue));

  if (q == NULL)
  {
    return -1;
  }
  (q->data).head = NULL;

  enqueue(q, start);
  while ((q->data).head != NULL)
  {
    struct game_state currentState = dequeue(q);

    if (completedGame(currentState))
    {
      return currentState.num_steps;
    }
    else
    {
      struct game_state nextState = currentState;
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
    }
  }

  return 0;
}

bool completedGame(struct game_state state)
{
  int correctness = 0; // check if the state of the game is at the end or not
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      if (state.tiles[i][j] == 4 * i + j + 1|| (state.tiles[state.empty_row][state.empty_col] == 0 && state.empty_row == i && state.empty_col == j))
      {
        correctness++;
      }
    }
  }
  return ((correctness == 16) ? true : false);
}
