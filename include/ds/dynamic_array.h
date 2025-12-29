#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

typedef struct {
  int x;
  int y;
} Point;

typedef struct {
  Point *array;
  int capacity;
  int end_idx;
} DynamicArray;

typedef enum {
  ARRAY_OK = 0,
  ARRAY_EMPTY = -1,
  ARRAY_ERR_MEM = -2,
  ARRAY_ERR_NULL = -3
} ARRAY_ERRORS;

DynamicArray *array_init(int capacity);
int array_resize(DynamicArray *array);
void array_free(DynamicArray *array);
int array_push(DynamicArray *array, int x, int y);
Point array_pop_front(DynamicArray *array); // FIFO
Point array_pop_end(DynamicArray *array);   // LIFO
Point array_pop_random(DynamicArray *array);
#endif // !DYNAMIC_ARRAY_H
