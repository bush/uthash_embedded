#ifndef UTHASH_EMBEDDED_H
#define UTHASH_EMBEDDED_H

#include "uthash.h"

typedef struct ute_htbl_s {
  UT_hash_table tbl;
  UT_hash_bucket bkts[HASH_INITIAL_NUM_BUCKETS];
} ute_htbl_t;

typedef struct ute_node_s {
  struct ute_node_s *next;
  struct ute_node_s *prev;
  ute_htbl_t *htbl;
  UT_hash_handle hh;
} ute_node_t;

void *ute_init_nodes(char *container, uint32_t container_size, u_int32_t node_size);

#endif /* UTHASH_EMBEDDED_H */
