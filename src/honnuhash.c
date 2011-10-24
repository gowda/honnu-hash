#define _GNU_SOURCE
#include <stdio.h>

#include <stdlib.h>

#include "hash-map.h"

int main (int argc, char *argv[])
{
        hash_map_t *map = NULL;
        char *key = NULL, *value = NULL;
        int idx = 0, r = 0;

        map = hash_map_init ();
        if (map == NULL) {
                printf ("failed to initialize hash map\n");
        }

        for (idx = 0; idx < 100; idx++) {
                asprintf (&key, "%d", idx);
                asprintf (&value, "%04d", (1000 - idx));

                hash_map_set (map, key, value);

                free (key);
                free (value);
        }

        /* delete twenty (20) entries from the hash-map randomly */
        for (idx = 0; idx < 10; idx++) {
                r = (random ()) % 10;
                asprintf (&key, "%d", r);

                hash_map_unset (map, key);

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

                        free (value);

                        ++idx;
                }

                free (key);
        }

        return 0;
}
