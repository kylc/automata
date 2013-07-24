typedef enum { ON, OFF } cell_state;

struct cells_t {
  int length;
  cell_state state[];
};

struct cells_t *cells_new(int length, cell_state defval);
void cells_set_state(struct cells_t *cells, int idx, int st);
cell_state cells_get_state(struct cells_t *cells, int idx);
