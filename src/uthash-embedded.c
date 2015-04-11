#include <stdio.h>
#include "uthash.h"



#if 0

/* TODO - Adapt uthash to take two allocations function as parameter.
 *        This way we can pass in our containers directly when we add something */

void wra_tm_init(wra_uthash_table_t *uthash_table)
{
  return;
}



void * wra_uthash_malloc(size_t size)
{
  if(size == sizeof(UT_hash_table))
    return table;
}
#endif
