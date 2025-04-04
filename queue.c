#include "queue.h"
#include "tile_game.h"
bool completedGame(struct game_state);

void enqueue(struct queue *q, struct game_state state) 
{
  size_t serializedState = serialize(state);
  insert_at_tail(&(q -> data), serializedState);
  return;
}

struct game_state dequeue(struct queue *q) 
{ 
  struct game_state removedGameState = deserialize((remove_from_head(&q -> data)));
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
  struct queue q;
  enqueue(&q, start);
  while (q.data.head != NULL)
  {
    struct game_state currentState = dequeue(&q);
    if (completedGame(currentState))
    {
      return currentState.num_steps;
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
      if(state.tiles[i][j] == 4 * i + j || state.tiles[state.empty_row][state.empty_col] == 0) {correctness++;}
    } 
  }
  return ((correctness == 16) ? true : false);
}
