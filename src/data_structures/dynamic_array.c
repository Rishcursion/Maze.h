#include "dynamic_array.h"
#include <stdlib.h>

/* NOTE: Struct definitions for Node and Frontier are REMOVED.
   They are already defined in dynamic_array.h.
   Redefining them here creates two different types that don't match!
*/

Frontier *array_init(int initial_capacity) {
  Frontier *new_frontier = NULL;
  new_frontier = (Frontier *)malloc(sizeof(Frontier));
  if (new_frontier == NULL) {
    return NULL;
  }
  new_frontier->capacity = initial_capacity;

  // Allocate the block of Nodes
  new_frontier->node = (Node *)calloc(initial_capacity, sizeof(Node));
  if (new_frontier->node == NULL) {
    free(new_frontier);
    return NULL;
  }

  new_frontier->num_elements = 0;
  return new_frontier;
}

int array_push(Frontier *frontier, int x_coord, int y_coord) {
  // If the array is full, resize it
  int result = EXIT_SUCCESS;
  if (frontier->capacity == frontier->num_elements) {
    result = array_resize(frontier, 2.0);
  }
  if (result == EXIT_FAILURE) {
    return result;
  }

  // Create temp node and assign
  Node new_node = {x_coord, y_coord};
  frontier->node[frontier->num_elements] = new_node;
  frontier->num_elements += 1;

  return EXIT_SUCCESS;
}

int array_resize(Frontier *frontier, float factor) {
  // Guard clause: Only resize if actually full
  if (frontier->capacity > frontier->num_elements) {
    return EXIT_SUCCESS;
  }

  int new_capacity = (int)(frontier->capacity * factor);
  Node *temp = (Node *)realloc(frontier->node, new_capacity * sizeof(Node));

  if (temp == NULL) {
    // Resize failed, keep original data intact
    return EXIT_FAILURE;
  }

  frontier->node = temp;
  frontier->capacity = new_capacity;
  return EXIT_SUCCESS;
}

Node array_delete_random(Frontier *frontier) {
  // Pick random index
  int delete_idx = rand() % frontier->num_elements;

  // Swap-and-Pop: Replace chosen node with the last node
  Node deleted_node = frontier->node[delete_idx];
  frontier->node[delete_idx] = frontier->node[frontier->num_elements - 1];

  frontier->num_elements -= 1;
  return deleted_node;
}

void array_clean(Frontier *frontier) {
  if (frontier) {
    if (frontier->node) {
      free(frontier->node);
    }
    free(frontier);
  }
}
