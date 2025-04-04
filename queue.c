#include "queue.h"
#include "tile_game.h"

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

int number_of_moves(struct game_state start) 
{
  return 0; 
}
