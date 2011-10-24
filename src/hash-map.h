#ifndef __HASH_MAP_H__
#define __HASH_MAP_H__


typedef struct node {
        struct node *next;
        char *key;
        char *value;
} hash_map_t;


hash_map_t *hash_map_init (int limit);


hash_map_t *hash_map_set (hash_map_t *map,
                          char *key,
                          char *value);

char *hash_map_get (hash_map_t *map,
                    char *key);

int hash_map_dump (hash_map_t *map);

#endif /* __HASH_MAP__ */
