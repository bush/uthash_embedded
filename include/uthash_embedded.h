#ifndef UTHASH_EMBEDDED_H
#define UTHASH_EMBEDDED_H

#include "uthash.h"

typedef struct ute_node_s {
  struct ute_node_s *next;
  struct ute_node_s *prev;
  UT_hash_handle hh;
} ute_node_t;

#endif /* UTHASH_EMBEDDED_H */
