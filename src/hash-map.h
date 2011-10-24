#ifndef __HASH_MAP_H__
#define __HASH_MAP_H__

#include "list.h"

typedef struct node {
        struct list_head nodes;
        char *key;
        char *value;
} hash_map_t;


hash_map_t *hash_map_init (void);


hash_map_t *hash_map_set (hash_map_t *map,
                          char *key,
                          char *value);

char *hash_map_get (hash_map_t *map,
                    char *key);

hash_map_t *hash_map_unset (hash_map_t *map,
                            char *key);

int hash_map_dump (hash_map_t *map);

#endif /* __HASH_MAP__ */
