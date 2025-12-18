#include "dynamic_array.h"
#include "stdio.h"
#include <stdlib.h>

struct Node {
  int x_coord;
  int y_coord;
};

struct Frontier {
  Node *node;
  int capacity;
  int num_elements;
};

Frontier *array_init(int initial_capacity) {
  Frontier *new_frontier = NULL;
  new_frontier = (Frontier *)malloc(sizeof(Frontier));
  if (new_frontier == NULL) {
    return NULL;
  }
  new_frontier->capacity = initial_capacity;
  Node *new_block = (Node *)calloc(sizeof(Node), initial_capacity);
  if (new_block == NULL) {
    free(new_frontier);
    return NULL;
  }
  new_frontier->node = new_block;
  new_frontier->num_elements = 0;
  return new_frontier;
}

int array_push(Frontier *frontier, int x_coord, int y_coord) {
  // If the array is full, resize it by a defined factor, otherwise continue
  // with push operation
  int result = EXIT_SUCCESS;
  if (frontier->capacity == frontier->num_elements) {
    result = array_resize(frontier, 2.0);
  }
  if (result == EXIT_FAILURE) {
    return result;
  }
  Node new_node = {x_coord, y_coord};
  frontier->num_elements += 1;
  frontier->node[frontier->num_elements - 1] = new_node;
  return EXIT_SUCCESS;
}
int array_resize(Frontier *frontier, float factor) {
  // Double check whether array needs reallocation just in case
  if (frontier->capacity > frontier->num_elements) {
    return EXIT_SUCCESS;
  }
  frontier->capacity *= factor;
  Node *temp =
      (Node *)realloc(frontier->node, frontier->capacity * sizeof(Node));
  if (temp == NULL) {
    frontier->capacity /= factor;
    return EXIT_FAILURE;
  }
  frontier->node = temp;
  return EXIT_SUCCESS;
}
Node array_delete_random(Frontier *frontier) {
  int delete_idx = rand() % frontier->num_elements;
  Node deleted_node = frontier->node[delete_idx];
  frontier->node[delete_idx] = frontier->node[frontier->num_elements - 1];
  frontier->num_elements -= 1;
  return deleted_node;
};

void array_clean(Frontier *frontier) {
  free(frontier->node);
  frontier->node = NULL;
  free(frontier);
  frontier = NULL;
}
