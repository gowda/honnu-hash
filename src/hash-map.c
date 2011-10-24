#include <stdlib.h>
#include <string.h>

#include "hash-map.h"

hash_map_t *hash_map_init (int limit)
{
        hash_map_t *head = NULL;

        head = calloc (1, sizeof (hash_map_t));

        return head;
}


hash_map_t *hash_map_set (hash_map_t *map,
                          char *key,
                          char *value)
{
        hash_map_t *node = NULL;

        node = calloc (1, sizeof (hash_map_t));

        node->key = strdup (key);
        node->value = strdup (value);

        node->next = map->next;

        map->next = node;

        return map;
}

char *hash_map_get (hash_map_t *map,
                    char *key)
{
        hash_map_t *node = NULL;

        for (node = map->next; node->next; node = node->next) {
                if (strcmp (key, node->key))
                        return strdup (node->value);
        }

        return NULL;
}

int hash_map_dump (hash_map_t *map)
{
        hash_map_t *node = NULL;

        for (node = map->next; node->next; node = node->next) {
                printf ("key: %s\t value: %s\n", node->key, node->value);
        }

        return 0;
}
