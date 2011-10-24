#include <stdio.h>

#include <stdlib.h>
#include <string.h>

#include "hash-map.h"

static int simple_hash_function (char *str)
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

static hash_node_t *__hash_map_get (hash_map_t *map,
                                    char *key)
{
        hash_node_t *node = NULL, *tmp = NULL;
        int hash = 0;

        hash = simple_hash_function (key);

        list_for_each_entry (node, &map->hashes[hash], hash) {
                if (0 == strcmp (key, node->key))
                        tmp = node;
        }

        return tmp;
}

hash_map_t *hash_map_set (hash_map_t *map,
                          char *key,
                          char *value)
{
        hash_node_t *node = NULL;
        char *old_value = NULL;
        int hash = 0;

        node = __hash_map_get (map, key);
        if (node) {
                free (node->key);
                free (node->value);

                goto just_set;
        }

        node = calloc (1, sizeof (hash_node_t));

        INIT_LIST_HEAD (&node->nodes);
        INIT_LIST_HEAD (&node->hash);

        list_add (&node->nodes, &map->nodes);

        hash = simple_hash_function (key);
        list_add (&node->hash, &map->hashes[hash]);

just_set:
        node->key = strdup (key);
        node->value = strdup (value);

        return map;
}

char *hash_map_get (hash_map_t *map,
                    char *key)
{
        hash_node_t *node = NULL;
        char *value = NULL;

        node = __hash_map_get (map, key);

        if (node)
                value = strdup (node->value);

        return value;
}

hash_map_t *hash_map_unset (hash_map_t *map,
                            char *key)
{
        hash_node_t *node = NULL;

        node = __hash_map_get (map, key);

        if (node) {
                list_del_init (&node->nodes);
                list_del_init (&node->hash);

                free (node->key);
                free (node->value);

                free (node);
        }

        return map;
}

int hash_map_dump (hash_map_t *map)
{
        int idx = 0;
        int count = 0;
        hash_node_t *node = NULL;

        for (idx = 0; idx < HASHMAX; idx++) {
                if (!list_empty (&map->hashes[idx])) {
                        list_for_each_entry (node, &map->hashes[idx], hash) {
                                count++;
                        }
                        printf ("hash value - %d ==> %d entries\n",
                                idx, count);
                        count = 0;
                }
        }

        count = 0;
        list_for_each_entry (node, &map->nodes, nodes) {
                count++;
        }
        printf ("total entries - %d\n", count);

        return 0;
}
