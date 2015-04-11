#include <stdio.h>
#include "uthash-embedded.h"

struct my_struct {
  int id;                    /* key */
  char name[10];
  UT_hash_handle hh;         /* makes this structure hashable */
};

struct my_struct *users = NULL;

typedef struct wra_uthash_table_st {
  UT_hash_table table;
  UT_hash_bucket buckets[HASH_INITIAL_NUM_BUCKETS];
} wra_uthash_table_t;

int main(int argc, char *argv[])
{
  struct my_struct *s = NULL;
  struct my_struct *find = NULL;
  char name[10] = "Dave Bush";
  int user_id = 1;

  printf("Size of UT_hash_table: %d\n",sizeof(UT_hash_table));
  printf("Size of UT_hash_bucket: %d\n",sizeof(UT_hash_bucket));
  printf("HASH_INITIAL_NUM_BUCKETS: %d\n",HASH_INITIAL_NUM_BUCKETS);

  s = malloc(sizeof(struct my_struct));
  s->id = user_id;
  strcpy(s->name, name);
  HASH_ADD_INT( users, id, s );  /* id: name of key field */
  HASH_FIND_INT( users, &user_id, find );  /* id: name of key field */
  if(find) printf("Found entry: %s\n",find->name);
  else printf("Entry not found\n");

  return 0;
}
