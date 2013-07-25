#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "cells.h"

#define CELLS_WIDTH 500
#define GENERATIONS 250

bool pattern_matches(struct cells_t *cells, size_t idx, cell_state a, cell_state b,
    cell_state c) {

  if(idx > cells_length(cells) - 1) {
    return false;
  }

  return cells_get_state(cells, idx - 1) == a
      && cells_get_state(cells, idx)     == b
      && cells_get_state(cells, idx + 1) == c;
}

cell_state rule_30_pattern(struct cells_t *cells, size_t i) {
  if(pattern_matches(cells, i, ON, OFF, OFF)
      || pattern_matches(cells, i, OFF, ON, ON)
      || pattern_matches(cells, i, OFF, ON, OFF)
      || pattern_matches(cells, i, OFF, OFF, ON)) {
    return ON;
  }

  return OFF;
}

struct cells_t *rule_30(struct cells_t *cells) {
  struct cells_t *new_cells = cells_copy(cells);

  for(size_t i = 1; i < cells_length(cells) - 1; i++) {
    cell_state newval = rule_30_pattern(cells, i);
    cells_set_state(new_cells, i, newval);
  }

  return new_cells;
}

int main(int argc, char **argv) {
  struct cells_t *cells = cells_new(CELLS_WIDTH, OFF);
  cells_set_state(cells, CELLS_WIDTH / 2, ON);

  FILE *fptr = fopen("output.pbm", "w");
  cells_write_pbm_header(cells, fptr, CELLS_WIDTH, GENERATIONS);

  struct cells_t *new_cells;
  for(int gen = 0; gen < GENERATIONS; gen++) {
    new_cells = rule_30(cells);
    cells_free(cells);
    cells = new_cells;

    cells_write_pbm_generation(cells, fptr);
  }
  cells_free(new_cells);

  fclose(fptr);

  return EXIT_SUCCESS;
}
