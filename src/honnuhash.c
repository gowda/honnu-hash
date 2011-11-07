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

#define _GNU_SOURCE
#include <stdio.h>

#include <stdlib.h>

#include <sys/types.h>
#include <unistd.h>

#include "hash-map.h"

#define HH_LIMIT 1024

static void hh_random_init (void)
{
        pid_t hh_pid = 0;

        hh_pid = getpid();

        srandom (hh_pid);
}

static int hh_random (void)
{
        /* don't want zero as a random value */
        return ((random() % HH_LIMIT) + 1);
}

int main (int argc, char *argv[])
{
        hash_map_t *map = NULL;
        char *key = NULL, *value = NULL, *old_value = NULL;
        int idx = 0, r = 0;

        map = hash_map_init ();
        if (map == NULL) {
                printf ("failed to initialize hash map\n");
        }

        hh_random_init ();

        /* insert 100 random entries
         * key - random number in the range 0 - 100
         * value - 1000000 % key
         */
        for (idx = 0; idx < 100; idx++) {
                r = hh_random ();

                asprintf (&key, "%d", r);
                asprintf (&value, "%04d", ((HH_LIMIT * HH_LIMIT + 1) % r));

                old_value = hash_map_set (map, key, value);

                if (old_value) {
                        free (old_value);
                        old_value = NULL;
                }

                free (key);
        }

        /* delete twenty (20) entries from the hash-map randomly */
        value = NULL;
        for (idx = 0; idx < 10; idx++) {
                r = hh_random();
                asprintf (&key, "%d", r);

                value = hash_map_unset (map, key);

                free (value);

                free (key);
        }

        /* retrieve ten entries from the hash-map randomly */
        idx = 0;
        while (idx < 10) {
                r = hh_random();
                asprintf (&key, "%d", r);

                value = hash_map_get (map, key);
                if (value) {
                        printf ("(key, value) ==> (%s, %s)\n", key, value);

                        ++idx;
                }

                free (key);
        }

        hash_map_dump (map);

        return 0;
}
