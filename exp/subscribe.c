#include <string.h>  /* strcpy */
#include <stdlib.h>  /* malloc */
#include <stdio.h>   /* printf */
#include "uthash.h"
#include "utlist.h"

/* Subscription structure */
typedef struct wra_subscription_st {
  char key[100];
  char app_key[50];
  int app_id;
  void *cookie;
  struct wra_subscription_st *next;
  UT_hash_handle hh;
} wra_subscription_t;

typedef struct wra_applist_st {
  char key[100];
  char type[25];
  char subscription_key[25];
  wra_subscription_t *head;
  UT_hash_handle hh;
} wra_applist_t;


typedef struct wra_subscription_table_st {
  int reserved_for_lock;
  wra_applist_t *applist;
  wra_subscription_t *subscriptions;
} wra_subscription_table_t;

int app_id = 1;

void delete_all(wra_subscription_table_t *tbl) {
  wra_subscription_t *current_user, *tmp;
  HASH_ITER(hh, tbl->subscriptions, current_user, tmp) {
    HASH_DEL(tbl->subscriptions,current_user);
    free(current_user);
  }
}

void print_subscription_table(wra_subscription_table_t *tbl)
{
  wra_subscription_t *subscription;

  for(subscription=tbl->subscriptions; subscription != NULL;
      subscription=(wra_subscription_t*)(subscription->hh.next)) {
    printf("key: %s\n",subscription->key);
  }
}

wra_subscription_t *wra_subscribe_find(wra_subscription_table_t *tbl, char *key)
{
  wra_subscription_t *subscription;

  printf("looking for |%s|\n",key);
  HASH_FIND_STR(tbl->subscriptions,key,subscription);
  if (subscription) return subscription;
  return NULL;
}

wra_subscription_table_t *wra_subscribe(wra_subscription_table_t *tbl,
                   char *type, char *subscription_key, char *app_key) {
  wra_subscription_t *subscription;
  wra_applist_t *applist;
  char key[100];
  char applist_key[100];
  
  memset(key,'\0',sizeof(key));
  strncat(key,subscription_key,sizeof(key));
  strncat(key,"-",1);
  strncat(key,app_key,sizeof(key));
  strncat(key,"-",1);
  strncat(key,type,sizeof(key));

  /* Check for an existing subscritpiotn */
  HASH_FIND_STR(tbl->subscriptions,key,subscription);

  /* No existing subscription so create one */
  if(subscription == NULL)
  {
    /* Add the tm name as the primary key */
    subscription = (wra_subscription_t*)malloc(sizeof(wra_subscription_t));
    if(subscription == NULL)
    {
      printf("wra_subscribe :: malloc failed\n");
      return;
    }

    /* Populate the subscription node */
    subscription->app_id = app_id++;
    memset(subscription->key,'\0',sizeof(subscription->key));
    strncpy(subscription->key,key,sizeof(subscription->key));
    strncpy(subscription->app_key,app_key,sizeof(subscription->app_key));
    HASH_ADD_STR(tbl->subscriptions,key,subscription);

    /* Create the type-subscription key */
    memset(applist_key,'\0',sizeof(applist_key));
    strncpy(applist_key,type,sizeof(applist_key));
    strncat(applist_key,"-",1);
    strncat(applist_key,subscription_key,sizeof(applist_key));

    /* Now find the applist node */
    HASH_FIND_STR(tbl->applist,applist_key,applist);

    /* No applist for this subscription key so create a node and add it */
    if(applist == NULL)
    {
      applist = (wra_applist_t*)malloc(sizeof(wra_applist_t));

      /* Copy the key */
      memset(applist->key,'\0',sizeof(applist->key));
      strncpy(applist->key,applist_key,sizeof(applist->key));

      /* Copy the subscription key */
      memset(applist->subscription_key,'\0',sizeof(applist->subscription_key));
      strncpy(applist->subscription_key,subscription_key,sizeof(applist->subscription_key));

      /* Copy the type */
      memset(applist->type,'\0',sizeof(applist->type));
      strncpy(applist->type,type,sizeof(applist->type));

      HASH_ADD_STR(tbl->applist,key,applist);
    }

    /* Add it to the list */
    LL_APPEND(applist->head,subscription);
  }

  else
    printf("App %s already subscribed for %s:%s\n",app_key,type,subscription_key);

  return subscription;

}

int main(int argc, char *argv[])
{
  wra_applist_t *applist, *tmp;
  wra_subscription_t *subscription, *tmp1, *add;
  wra_subscription_table_t stable;

  /* Initialize */
  stable.subscriptions = NULL;
  stable.applist = NULL;

  add = wra_subscribe(&stable,"tm","temp","app1");
  /* Add custom cookies here */


  wra_subscribe(&stable,"tm","temp","app2");
  wra_subscribe(&stable,"tm","temp","app3"); 
  wra_subscribe(&stable,"tm","temp","app4"); 
  wra_subscribe(&stable,"tm","pressure","app1"); 
  wra_subscribe(&stable,"file","temp","app1");
  wra_subscribe(&stable,"file","temp","app5");
  wra_subscribe(&stable,"file","foobar.txt","app1");

  printf("Subscriptions:\n");
  HASH_ITER(hh,stable.subscriptions,subscription,tmp1) {
    printf("key :: '%s'\n", subscription->key);
  }

  printf("Apps:\n");
  HASH_ITER(hh,stable.applist,applist,tmp) {
    printf("Subscription :: '%s' '%s:%s'\n",applist->key, applist->type, applist->subscription_key);
    LL_FOREACH(applist->head,subscription)
      printf("\tApp :: '%s'\n",subscription->app_key);
  }

  return 0;
}
