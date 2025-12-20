#ifndef dynamic_array_h
#define dynamic_array_h
#include <stddef.h>

typedef struct {
  int x_coord;
  int y_coord;
} Node;

typedef struct {
  Node *node;
  int capacity;
  int num_elements;
} Frontier;

Frontier *array_init(int initial_capacity);
/*Responsible for pushing an element in the array, and updating num_elements and
end_idx, will also be responsible for triggering array resize if
num_elements==capacity before pushing.*/
int array_push(Frontier *frontier, int x_coord, int y_coord);
// Resizes the array by doubling the bytes allocated to it
int array_resize(Frontier *frontier, float factor);
/* Picks a random element in the array to be deleted, results in two cases:
        i) Element in idx 0->Frontier.capacity-1:
         Copy the node at selected idx, replace with Frontier[end_idx], and
decrement num_elements and end_idx
        ii) Element is at end_idx:
            Return Node at end_idx, and decrement end_idx and num_elements
*/
Node array_delete_random(Frontier *frontier);
void array_clean(Frontier *frontier);
#endif // !dynamic_array_h
