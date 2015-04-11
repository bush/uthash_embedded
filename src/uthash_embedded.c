#include <stdio.h>
#include "uthash_embedded.h"
#include "uthash.h"
#include "utlist.h"


char *ute_init_nodes(const char *container, uint32_t container_size, u_int32_t node_size)
{
  node_t *head = NULL;
  node_t *node = (node_t *)container;
  u_int32_t remaining = container_size;
  
  /* Check for room */
  if(container_size < node_size) return NULL; 

  /* Setup the free list */
  while(remaining >= node_size)
  {
    printf("Adding node\n");
    DL_APPEND(head,node);
    remaining -= node_size;
    node += node_size;
  }

  return (char *)head;
}
