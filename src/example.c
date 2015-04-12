#include <stdio.h>
#include "uthash_embedded.h"

struct my_struct {
  ute_node_t node;
  int id;
  char name[10];
};

struct my_struct node_pool[10];

/* Users table */
struct my_struct *users = NULL;

ute_htbl_t my_htbl;

int main(int argc, char *argv[])
{
  int i;
  struct my_struct *ptr = node_pool;
#if 0
  struct my_struct *s = NULL;
  struct my_struct *find = NULL;
  char name[10] = "Dave Bush";
  int user_id = 1;
#endif

  printf("Size of UT_hash_table: %d\n",sizeof(UT_hash_table));
  printf("Size of UT_hash_bucket: %d\n",sizeof(UT_hash_bucket));
  printf("HASH_INITIAL_NUM_BUCKETS: %d\n",HASH_INITIAL_NUM_BUCKETS);

  for(i=0;i<10;i++) {
    printf("ptr: %p\n",ptr);
    ptr++;
  }

  printf("node_pool: %d, my_struct: %d\n",sizeof(node_pool),sizeof(struct my_struct));
  ute_init_nodes((char *)node_pool,sizeof(node_pool),sizeof(struct my_struct));

#if 0
  s = malloc(sizeof(struct my_struct));
  s->node.htbl = &my_htbl;
  s->id = user_id;
  strcpy(s->name, name);
  HASH_ADD_INT( users, id, s );  /* id: name of key field */
  HASH_FIND_INT( users, &user_id, find );  /* id: name of key field */
  if(find) printf("Found entry: %s\n",find->name);
  else printf("Entry not found\n");
#endif
  return 0;
}
