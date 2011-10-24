#include <stdio.h>

#include <stdlib.h>
#include <string.h>

#include "hash-map.h"

int simple_hash_function (char *str)
{
        int len = 0;
        int idx = 0;
        int sum = 0;
        int hash = 0;

        len = strlen (str);

        for (idx = 0; idx < len; idx++)
                sum += str[idx];

        hash = sum % HASHMAX;

        return hash;
}

hash_map_t *hash_map_init (void)
{
        hash_map_t *head = NULL;
        int idx = 0;

        head = calloc (1, sizeof (hash_map_t));

        INIT_LIST_HEAD (&head->nodes);
        for (idx = 0; idx < HASHMAX; idx ++)
                INIT_LIST_HEAD (&head->hashes[idx]);

        return head;
}


hash_map_t *hash_map_set (hash_map_t *map,
                          char *key,
                          char *value)
{
        hash_node_t *node = NULL;
        char *old_value = NULL;
        int hash = 0;

        old_value = hash_map_get (map, key);
        if (old_value) {
                hash_map_unset (map, key);
                free (old_value);
        }

        node = calloc (1, sizeof (hash_node_t));

        INIT_LIST_HEAD (&node->nodes);
        INIT_LIST_HEAD (&node->hash);

        node->key = strdup (key);
        node->value = strdup (value);

        list_add (&node->nodes, &map->nodes);

        hash = simple_hash_function (key);
        list_add (&node->hash, &map->hashes[hash]);

        return map;
}

char *hash_map_get (hash_map_t *map,
                    char *key)
{
        hash_node_t *node = NULL;
        int hash = 0;

        hash = simple_hash_function (key);

        list_for_each_entry (node, &map->hashes[hash], hash) {
                if (0 == strcmp (key, node->key))
                        return strdup (node->value);
        }

        return NULL;
}

hash_map_t *hash_map_unset (hash_map_t *map,
                            char *key)
{
        hash_node_t *node = NULL, *tmp = NULL;
        int hash = 0;

        hash = simple_hash_function (key);


        list_for_each_entry (node, &map->hashes[hash], hash) {
                if (0 == strcmp (key, node->key)) {
                        tmp = node;
                        break;
                }
        }

        if (tmp) {
                list_del_init (&tmp->nodes);
                list_del_init (&tmp->hash);

                free (tmp->key);
                free (tmp->value);

                free (tmp);
        }

        return map;
}

int hash_map_dump (hash_map_t *map)
{
        hash_node_t *node = NULL;

        list_for_each_entry (node, &map->nodes, nodes) {
                printf ("key: %s\t value: %s\n", node->key, node->value);
        }

        return 0;
}
