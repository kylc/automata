typedef enum { OFF, ON } cell_state;

struct cells_t {
  size_t length;
  cell_state state[];
};

struct cells_t *cells_new(size_t length, cell_state defval);
void cells_free(struct cells_t *cells);
struct cells_t *cells_copy(struct cells_t *old_cells);
size_t cells_length(struct cells_t *cells);
void cells_set_state(struct cells_t *cells, size_t idx, cell_state st);
cell_state cells_get_state(struct cells_t *cells, size_t idx);

void cells_write_pbm_header(struct cells_t *cells, FILE *fptr, int width, int height);
void cells_write_pbm_generation(struct cells_t *cells, FILE *fptr);
