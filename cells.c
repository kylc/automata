#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cells.h"

struct cells_t *cells_new(int length, cell_state defval) {
  struct cells_t *cells = malloc(sizeof(struct cells_t) + length * sizeof(cell_state));

  cells->length = length;
  for(int i = 0; i < length; i++) {
    cells->state[i] = defval;
  }

  return cells;
}

void cells_free(struct cells_t *cells) {
  free(cells);
}

struct cells_t *cells_copy(struct cells_t *old_cells) {
  struct cells_t *new_cells = cells_new(old_cells->length, 0);

  memcpy(new_cells->state, new_cells->state, new_cells->length * sizeof(cell_state));

  return new_cells;
}

size_t cells_length(struct cells_t *cells) {
  return cells->length;
}

void cells_set_state(struct cells_t *cells, int idx, int st) {
  cells->state[idx] = st;
}

cell_state cells_get_state(struct cells_t *cells, int idx) {
  return cells->state[idx];
}

void cells_write_pbm_header(struct cells_t *cells, FILE *fptr, int width, int height) {
  fprintf(fptr, "P1\n"); // <type>
  fprintf(fptr, "%d %d\n", width, height); // <width> <height>
}

void cells_write_pbm_generation(struct cells_t *cells, FILE *fptr) {
  for(int i = 0; i < cells_length(cells); i++) {
    fprintf(fptr, "%d ", cells_get_state(cells, i));

    // No more than 70 characters per line
    if(i % 25 == 0) {
      fprintf(fptr, "\n");
    }
  }
}
