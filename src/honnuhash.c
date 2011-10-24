#include <stdio.h>

#include "hash-map.h"

int main (int argc, char *argv[])
{
        hash_map_t *map = NULL;
        char *key = NULL, *value = NULL;
        int idx = 0;

        map = hash_map_init (100);
        if (map == NULL) {
                printf ("failed to initialize hash map\n");
        }

        for (idx = 0; idx < 100; idx++) {
                asprintf (&key, "%d", idx);
                asprintf (&value, "%04d", (1000 - idx));

                hash_map_set (map, key, value);
        }

        hash_map_dump (map);

        return 0;
}
