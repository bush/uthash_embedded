#ifndef UTHASH_EMBEDDED_H
#define UTHASH_EMBEDDED_H

#include "uthash.h"

typedef struct node_s {
  struct node_s *next, *prev;
} node_t;

#endif /* UTHASH_EMBEDDED_H */
