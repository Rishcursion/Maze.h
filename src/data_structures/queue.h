#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h> // For EXIT_SUCCESS/FAILURE context if needed

typedef struct QNode {
  int x_coord;
  int y_coord;
  struct QNode *next;
} QueueNode;

typedef struct {
  QueueNode *head;
  QueueNode *tail;
  int count;
} Queue;

// Function Prototypes
Queue *queue_init(void);
int queue_push(Queue *queue, int x, int y);
QueueNode *queue_pop(Queue *queue);
int queue_free(Queue *queue);

#endif // QUEUE_H
