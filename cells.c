#include <cells.h>

struct cells_t *cells_new(int length, cell_state defval) {
  struct cells_t *cells = malloc(sizeof(struct cells_t) + length * sizeof(cell_state));

  cells->length = length;
  for(int i = 0; i < length; i++) {
    cells->state[i] = defval;
  }

  return cells;
}

void cells_set_state(struct cells_t *cells, int idx, int st) {
  cells->state[idx] = st;
}

cell_state cells_get_state(struct cells_t *cells, int idx) {
  return cells->state[idx];
}

