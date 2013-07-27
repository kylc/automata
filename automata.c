#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "cells.h"

#define CELLS_WIDTH 500
#define GENERATIONS 250

const cell_state PATTERNS[][3] = {
  {ON, ON, ON},
  {ON, ON, OFF},
  {ON, OFF, ON},
  {ON, OFF, OFF},
  {OFF, ON, ON},
  {OFF, ON, OFF},
  {OFF, OFF, ON},
  {OFF, OFF, OFF}
};

bool pattern_matches(struct cells_t *cells, size_t idx, cell_state a, cell_state b,
    cell_state c) {

  if(idx > cells_length(cells) - 1) {
    return false;
  }

  return cells_get_state(cells, idx - 1) == a
      && cells_get_state(cells, idx)     == b
      && cells_get_state(cells, idx + 1) == c;
}

cell_state lookup_rule_table(cell_state rule[8], struct cells_t *cells, size_t idx) {
  for(int i = 0; i < 8; i++) {
    if(pattern_matches(cells, idx, PATTERNS[i][0], PATTERNS[i][1], PATTERNS[i][2])) {
      return rule[i];
    }
  }

  fprintf(stderr, "Reached impossible pattern, quitting.\n");
  exit(EXIT_FAILURE);
}

struct cells_t *apply_rule(cell_state rule[8], struct cells_t *cells) {
  struct cells_t *new_cells = cells_copy(cells);

  for(size_t i = 1; i < cells_length(cells) - 1; i++) {
    cell_state newval = lookup_rule_table(rule, cells, i);
    cells_set_state(new_cells, i, newval);
  }

  return new_cells;
}

int main(int argc, char **argv) {
  if(argc < 2) {
    fprintf(stderr, "Usage: automata outfile\n");
    return EXIT_SUCCESS;
  }

  struct cells_t *cells = cells_new(CELLS_WIDTH, OFF);
  cells_set_state(cells, CELLS_WIDTH / 2, ON);

  FILE *fptr = fopen(argv[1], "w");
  cells_write_pbm_header(cells, fptr, CELLS_WIDTH, GENERATIONS);

  cell_state rule_30[] = { OFF, OFF, OFF, ON, ON, ON, ON, OFF };

  struct cells_t *new_cells;
  for(int gen = 0; gen < GENERATIONS; gen++) {
    new_cells = apply_rule(rule_30, cells);
    cells_free(cells);
    cells = new_cells;

    cells_write_pbm_generation(cells, fptr);
  }
  cells_free(new_cells);

  fclose(fptr);

  return EXIT_SUCCESS;
}
