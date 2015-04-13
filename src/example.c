#include <stdio.h>
#include "uthash_embedded.h"

typedef struct my_node_s {
  ute_node_t node;
  int id;
  char name[10];
  UT_hash_handle hh;
} my_node_t;

my_node_t node_pool[10];

/* Users table */
my_node_t *users = NULL;

ute_htbl_t my_htbl;


int main(int argc, char *argv[])
{
  int i;
  my_node_t *ptr = node_pool;
  ute_node_t *head;
  ute_node_t *node_store[10];
  my_node_t *s, *find = NULL;
  int user_id = 1;

  printf("Size of UT_hash_table: %d\n",sizeof(UT_hash_table));
  printf("Size of UT_hash_bucket: %d\n",sizeof(UT_hash_bucket));
  printf("HASH_INITIAL_NUM_BUCKETS: %d\n",HASH_INITIAL_NUM_BUCKETS);

  for(i=0;i<10;i++) {
    printf("ptr: %p\n",ptr);
    ptr++;
  }
  
  printf("node_pool: %d, my_struct: %d\n",sizeof(node_pool),sizeof(my_node_t));
  head = ute_init_nodes((char *)node_pool,sizeof(node_pool),sizeof(my_node_t));

#if 0
  ute_display_nodes(head);

  printf("Allocating nodes\n");

  for(i=0;i<10;i++) {

    node_store[i] = ute_node_alloc(&head);

    if(node_store[i])
      printf("alloc_node: %p\n",node_store[i]);
    else
      printf("Node pool exhausted\n");

    ute_display_nodes(head);
  }

  printf("Freeing nodes\n");

  for(i=0;i<10;i++) {
    ute_node_free(&head,node_store[i]);
    ute_display_nodes(head);
  }
#endif

#if 1
  s = (my_node_t *)ute_node_alloc(&head);
  s->id = user_id;
  strcpy(s->name, "dave");
  s->node.htbl = &my_htbl;

  HASH_ADD_INT(users,id,s);  /* id: name of key field */
  ute_display_nodes(head);
  HASH_FIND_INT( users, &user_id, find );  /* id: name of key field */

  if(find) printf("Found entry: %s\n",find->name);
  else printf("Entry not found\n");
#endif

  return 0;
}
