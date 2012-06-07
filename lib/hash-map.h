/*
   Copyright (c) 2011 Basavanagowda Kanur <basavanagowda (at) gmail (dot) com>
   This file is part of honnu-hash.

   honnu-hash is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published
   by the Free Software Foundation; either version 3 of the License,
   or (at your option) any later version.

   honnu-hash is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see
   <http://www.gnu.org/licenses/>.
*/

#ifndef __HASH_MAP_H__
#define __HASH_MAP_H__

#include "list.h"

#include <pthread.h>

#define HASHMAX 1024

typedef struct head {
        struct list_head nodes;
        struct list_head hashes[HASHMAX];
        pthread_mutex_t lock;
        int count;
} hash_map_t;

typedef struct node {
        struct list_head nodes;
        struct list_head hash;
        char *key;
        void *value;
} hash_node_t;


hash_map_t *hash_map_init (void);


void *hash_map_set (hash_map_t *map,
                    char *key,
                    void *value);

void *hash_map_get (hash_map_t *map,
                    char *key);

void *hash_map_unset (hash_map_t *map,
                      char *key);

int hash_map_dump (hash_map_t *map);

#endif /* __HASH_MAP__ */
