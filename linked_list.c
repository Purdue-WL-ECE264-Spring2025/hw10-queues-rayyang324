#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) 
{
  struct list_node* newNodePtr = malloc(sizeof(struct list_node));
  if (newNodePtr == NULL)
  {
    return NULL;
  }
  newNodePtr -> value = value;
  newNodePtr -> next = NULL;

  return newNodePtr; 
}

void insert_at_head(struct linked_list *list, size_t value) 
{
  struct list_node* newVal = new_node(value);
  newVal -> next = list -> head;
  list -> head = newVal;
  return;
}

void insert_at_tail(struct linked_list *list, size_t value) 
{
  struct list_node* newVal = new_node(value);
  
  // handles the problem where it is an empty list
  if (list -> head == NULL) 
  {
    list -> head = newVal;
    return;
  }

  struct list_node* addressToCheck = list -> head;
  while(addressToCheck -> next != NULL)
  {
    addressToCheck = addressToCheck -> next;
  }

  addressToCheck -> next = newVal; // adding in the new value at the end
  return;
}

size_t remove_from_head(struct linked_list *list)  
{
  if (list -> head == NULL) // handles empty list
  {
    return 0;
  }

  struct list_node* temp = (list -> head) -> next; // temp variable for list head
  free(list -> head);
  list -> head = temp;

  return (list -> head) -> value; 
}

size_t remove_from_tail(struct linked_list *list) 
{
  size_t val;
  struct list_node* addressToCheck;
  if (list -> head == NULL)
  {
    return 0;
  }
  if ((list -> head) -> next == NULL)
  {
    val = (list -> head) -> value;
    free(list -> head);
    list -> head = NULL;
    return val;
  }

  addressToCheck = list -> head;
  while((addressToCheck -> next) -> next != NULL)
  {
    addressToCheck = addressToCheck -> next;
  }
  val = (addressToCheck -> next) -> value;
  free(addressToCheck -> next);
  addressToCheck -> next = NULL;

  return val; 
}


void free_list(struct linked_list list) 
{
  while (list.head != NULL)
  {
    struct list_node* tempPtr = list.head ->next;
    free (list.head);
    list.head = tempPtr;
  }
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
