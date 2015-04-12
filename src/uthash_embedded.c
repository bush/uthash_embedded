/* utash retrofit helpers. */

#include <stdio.h>
#include "uthash_embedded.h"
#include "uthash.h"
#include "utlist.h"


void *ute_init_nodes(char *container, uint32_t container_size, u_int32_t node_size)
{
  ute_node_t *head = NULL;
  ute_node_t *node = (ute_node_t *)container;
  char *ptr = container;
  u_int32_t remaining = container_size;
  
  /* Check for room */
  if(container_size < node_size) return NULL; 

  /* Setup the free list */
  while(remaining >= node_size)
  {
    printf("Adding node: %p\n",ptr);
    DL_APPEND(head,node);
    remaining -= node_size;
    ptr += node_size;
    node = (ute_node_t *)ptr;
  }

  printf("head: %p\n",head);
  return head;
}

void *ute_htbl_alloc(void *head_node)
{
  ute_node_t *node;
  
  if(head_node == NULL)
    return NULL;
  
  node = (ute_node_t *)head_node;
   
  return (void *)&node->htbl->tbl;
}

void *ute_bkts_alloc(void *head_node)
{
  ute_node_t *node;
  
  if(head_node == NULL)
    return NULL;
  
  node = (ute_node_t *)head_node;
  
  return (void *)&node->htbl->bkts;
}
