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

        pthread_mutex_init (&head->lock, 0);

        INIT_LIST_HEAD (&head->nodes);
        for (idx = 0; idx < HASHMAX; idx ++)
                INIT_LIST_HEAD (&head->hashes[idx]);

        head->count = 0;

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

int __hash_map_set (hash_map_t *map,
                    hash_node_t *node)
{
        int hash = 0;

        list_add (&node->nodes, &map->nodes);

        hash = simple_hash_function (node->key);
        list_add (&node->hash, &map->hashes[hash]);

        map->count++;
        return 0;
}

void *__hash_map_unset (hash_map_t *map,
                        hash_node_t *node)
{
        void *value = NULL;

        list_del_init (&node->nodes);
        list_del_init (&node->hash);

        map->count--;

        free (node->key);

        value = node->value;
        node->value = NULL;

        free (node);

        return value;
}

void *hash_map_set (hash_map_t *map,
                    char *key,
                    void *value)
{
        hash_node_t *node = NULL, *old_node = NULL;
        void *old_value = NULL;

        pthread_mutex_lock (&map->lock);
        {
                old_node = __hash_map_get (map, key);
                if (old_node) {
                        old_value = __hash_map_unset (map, old_node);
                }
        }
        pthread_mutex_unlock (&map->lock);

        node = calloc (1, sizeof (hash_node_t));

        INIT_LIST_HEAD (&node->nodes);
        INIT_LIST_HEAD (&node->hash);

        node->key = strdup (key);
        node->value = value;

        pthread_mutex_lock (&map->lock);
        {
                __hash_map_set (map, node);
        }
        pthread_mutex_unlock (&map->lock);


        return old_value;
}

void *hash_map_get (hash_map_t *map,
                    char *key)
{
        hash_node_t *node = NULL;
        void *value = NULL;

        node = __hash_map_get (map, key);

        if (node)
                value = node->value;

        return value;
}


void *hash_map_unset (hash_map_t *map,
                            char *key)
{
        hash_node_t *node = NULL;
        void *value = NULL;

        pthread_mutex_lock (&map->lock);
        {
                node = __hash_map_get (map, key);
                if (node)
                        __hash_map_unset (map, node);

        }
        pthread_mutex_unlock (&map->lock);

        return value;
}

int hash_map_dump (hash_map_t *map)
{
        int idx = 0;
        int count = 0;
        hash_node_t *node = NULL;
        char stat_str[2048] = {0,}; /* FIXME: i might run out of index */
        char stat_str_len = 0;

        for (idx = 0; idx < HASHMAX; idx++) {
                pthread_mutex_lock (&map->lock);

                if (!list_empty (&map->hashes[idx])) {
                        list_for_each_entry (node, &map->hashes[idx], hash) {
                                count++;
                        }
                        sprintf ((stat_str + stat_str_len), " (%d ==> %d)",
                                idx, count);
                        stat_str_len = strlen (stat_str);
                        count = 0;
                }

                pthread_mutex_unlock (&map->lock);
        }

        pthread_mutex_lock (&map->lock);
        count = map->count;
        pthread_mutex_unlock (&map->lock);

        printf ("(hash ==> entries) -\n\t%s\n", stat_str);
        printf ("total entries - %d\n", count);

        return 0;
}
