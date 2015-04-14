#include <stdio.h>
#include "uthash_embedded.h"

typedef struct my_node_s {
  ute_node_t node;
  int id;
  char name[10];
  UT_hash_handle hh;
} my_node_t;

/* User nodes */
my_node_t user_nodes[10];
ute_node_t *user_node_list;

/* Users table */
ute_htbl_t users_htbl;
my_node_t *users = NULL;

int main(int argc, char *argv[])
{
  my_node_t *s, *find = NULL;
  int user_id = 1;

  /* Initialization */
  user_node_list = ute_init_nodes((char *)user_nodes,sizeof(user_nodes),sizeof(my_node_t));
 
  /* Create a user node */
  s = (my_node_t *)ute_node_alloc(&user_node_list);
  s->id = user_id;
  strcpy(s->name, "dave");

  /* Add the node */
  UTE_HASH_ADD_INT(&users_htbl,users,id,s);
  ute_display_nodes(user_node_list);

  /* Find the node */
  HASH_FIND_INT(users,&user_id,find);

  if(find) printf("Found entry: %s\n",find->name);
  else printf("Entry not found\n");

  HASH_DEL(users,find);
  ute_node_free(&user_node_list,(ute_node_t *)find);
  
  /* Find the node */
  HASH_FIND_INT(users,&user_id,find);
  ute_display_nodes(user_node_list);

  return 0;
}
