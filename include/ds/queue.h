#ifndef QUEUE_H
#define QUEUE_H

typedef struct Queue Queue;
typedef enum {
  QUEUE_OK = 0,
  QUEUE_EMPTY = -1,
  QUEUE_ERR_MEM = -2,
  QUEUE_ERR_NULL = -3
} QUEUE_ERRORS;

Queue *queue_init(void);
void queue_free(void);
int queue_push(Queue *q, int x, int y);
int queue_pop(Queue *q, int *out_x, int *out_y);

#endif // !QUEUE_H
