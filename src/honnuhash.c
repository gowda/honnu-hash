#define _GNU_SOURCE
#include <stdio.h>

#include <stdlib.h>

#include "hash-map.h"

int main (int argc, char *argv[])
{
        hash_map_t *map = NULL;
        char *key = NULL, *value = NULL, *old_value = NULL;
        int idx = 0, r = 0;

        map = hash_map_init ();
        if (map == NULL) {
                printf ("failed to initialize hash map\n");
        }

        /* insert 100 random entries
         * key - random number in the range 0 - 100
         * value - 1000000 % key
         */
        for (idx = 0; idx < 100; idx++) {
                r = random() % 100;

                asprintf (&key, "%d", r);
                asprintf (&value, "%04d", (1000000 % r));

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
                r = (random ()) % 10;
                asprintf (&key, "%d", r);

                value = hash_map_unset (map, key);

                free (value);

                free (key);
        }

        /* retrieve ten entries from the hash-map randomly */
        idx = 0;
        while (idx < 10) {
                r = (random ()) % 100;
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
