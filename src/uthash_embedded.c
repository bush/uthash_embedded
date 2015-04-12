#include <stdio.h>
#include "uthash_embedded.h"
#include "uthash.h"
#include "utlist.h"


ute_node_t *ute_init_nodes(ute_node_t *container, uint32_t container_size, u_int32_t node_size)
{
  ute_node_t *head = NULL;
  ute_node_t *node = container;
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

  return (ute_node_t *)head;
}
