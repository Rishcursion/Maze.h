#include "queue.h"
#include <stdlib.h>

Queue *queue_init(void) {
  Queue *new_queue = NULL;
  new_queue = (Queue *)malloc(sizeof(Queue));
  if (new_queue == NULL) {
    return NULL;
  }

  QueueNode *dummy_node = (QueueNode *)malloc(sizeof(QueueNode));
  if (dummy_node == NULL) {
    free(new_queue);
    return NULL;
  }
  // We use dummy node logic here, because fuck it why not, too much python DSA
  // istg
  dummy_node->x_coord = -1;
  dummy_node->y_coord = -1;
  dummy_node->next = NULL;
  new_queue->head = dummy_node;
  new_queue->tail = dummy_node;
  new_queue->count = 0;
  return new_queue;
}

int queue_push(Queue *push_queue, int x, int y) {
  QueueNode *node = NULL;
  node = (QueueNode *)malloc(sizeof(QueueNode));
  if (node == NULL) {
    return EXIT_FAILURE;
  }
  node->x_coord = x;
  node->y_coord = y;
  node->next = NULL;
  push_queue->tail->next = node;
  push_queue->tail = push_queue->tail->next;
  push_queue->count++;
  return EXIT_SUCCESS;
}

QueueNode *queue_pop(Queue *pop_queue) {
  /*
In the dummy node setup, we have the following structure
DUMMY_NODE -> NODE_TO_POP -> NEXT_NODE
========================================================
To pop NODE_TO_POP, we have to perform the following operations
i) store reference to NODE_TO_POP;
ii) link DUMMY_NODE to NEXT_NODE;
iii) Nullify NODE_TO_POP.next, to avoid accidental alteration to the list after
returning to user
  */
  if (pop_queue->count == 0) {
    return NULL;
  }
  QueueNode *temp = NULL;
  temp = pop_queue->head->next;
  pop_queue->head->next = temp->next;
  temp->next = NULL;
  pop_queue->count -= 1;
  if (pop_queue->count == 0) {
    pop_queue->tail = pop_queue->head;
  }
  return temp;
}

int queue_free(Queue *free_queue) {
  if (free_queue == NULL) {
    // Queue is already freed
    return EXIT_FAILURE;
  }
  QueueNode *traveller = free_queue->head;
  while (traveller != NULL) {
    QueueNode *temp = traveller->next;
    free(traveller);
    traveller = temp;
  }
  free(free_queue);
  return EXIT_SUCCESS;
}
