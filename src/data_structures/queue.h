#ifndef queue
#define queue

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
Queue *queue_init(void);
int queue_push(Queue *queue, int x, int y);
QueueNode *queue_pop(Queue *queue);
// Walk through the linked list to free every node;
int queue_free(Queue *queue);
#endif // !queue
