#include <stdio.h>

#include <stdlib.h>
#include <string.h>

#include "hash-map.h"

hash_map_t *hash_map_init (void)
{
        hash_map_t *head = NULL;

        head = calloc (1, sizeof (hash_map_t));

        INIT_LIST_HEAD (&head->nodes);

        return head;
}


hash_map_t *hash_map_set (hash_map_t *map,
                          char *key,
                          char *value)
{
        hash_map_t *node = NULL;
        char *old_value = NULL;

        old_value = hash_map_get (map, key);
        if (old_value) {
                hash_map_unset (map, key);
                free (old_value);
        }

        node = calloc (1, sizeof (hash_map_t));

        INIT_LIST_HEAD (&node->nodes);

        node->key = strdup (key);
        node->value = strdup (value);

        list_add (&node->nodes, &map->nodes);

        return map;
}

char *hash_map_get (hash_map_t *map,
                    char *key)
{
        hash_map_t *node = NULL;

        list_for_each_entry (node, &map->nodes, nodes) {
                if (0 == strcmp (key, node->key))
                        return strdup (node->value);
        }

        return NULL;
}

hash_map_t *hash_map_unset (hash_map_t *map,
                            char *key)
{
        hash_map_t *node = NULL, *tmp = NULL;

        list_for_each_entry_safe (node, tmp, &map->nodes, nodes) {
                if (0 == strcmp (key, node->key)) {
                        list_del_init (&node->nodes);
                        break;
                }
        }

        if (node) {
                free (node->key);
                free (node->value);
        }

        return map;
}

int hash_map_dump (hash_map_t *map)
{
        hash_map_t *node = NULL;

        list_for_each_entry (node, &map->nodes, nodes) {
                printf ("key: %s\t value: %s\n", node->key, node->value);
        }

        return 0;
}
