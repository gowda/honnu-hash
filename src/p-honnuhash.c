/*
   Copyright (c) 2012 Basavanagowda Kanur <basavanagowda (at) gmail (dot) com>
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

#include <pthread.h>

#include "hash-map.h"

#define HH_LIMIT 1024

#define ACTION_INSERTION 1
#define ACTION_REMOVAL 2
#define ACTION_RETRIEVAL 3

struct thread_info {
  pthread_t thread_id;
  unsigned int action;
  unsigned int size;
  pthread_barrier_t *barrier;
  hash_map_t *map;
};

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

int insertions (hash_map_t *map, int size)
{
  int idx = 0, r = 0;
  char *key = NULL, *value = NULL, *old_value = NULL;
  int ret = -1;

  /* insert @size random entries
   * key - random number in the range 0 - 100
   * value - 1000000 % key
   */
  for (idx = 0; idx < 100; idx++) {
    r = hh_random ();

    ret = asprintf (&key, "%d", r);
    if (ret < 0)
      printf ("ERROR: asprintf failed\n");

    ret = asprintf (&value, "%04d", ((HH_LIMIT * HH_LIMIT + 1) % r));
    if (ret < 0)
      printf ("ERROR: asprintf failed\n");
      
    old_value = hash_map_set (map, key, value);

    if (old_value) {
      free (old_value);
      old_value = NULL;
    }

    free (key);
  }
}

int removals (hash_map_t *map, int size)
{
  int idx = 0, r = 0;
  char *key = NULL, *value = NULL;
  int ret = -1;

  /* delete @size entries from the hash-map randomly */

  value = NULL;
  for (idx = 0; idx < size; idx++) {
    r = hh_random();

    ret = asprintf (&key, "%d", r);
    if (ret < 0)
      printf ("ERROR: asprintf failed\n");

    value = hash_map_unset (map, key);

    free (value);

    free (key);
  }

}

int retrievals (hash_map_t *map, int size)
{
  int idx = 0, r = 0;
  char *key = NULL, *value = NULL;
  int ret = -1;

  /* retrieve @size entries from the hash-map randomly */
  idx = 0;
  while (idx < size) {
    r = hh_random();
    ret = asprintf (&key, "%d", r);
    if (ret < 0)
      printf ("ERROR: asprintf failed\n");

    value = hash_map_get (map, key);
    if (value) {
      printf ("(key, value) ==> (%s, %s)\n", key, value);

      ++idx;
    }

    free (key);
  }

}

static void *thread_start (void *arg)
{
  struct thread_info *tinfo = (struct thread_info *) arg;

  pthread_barrier_wait (tinfo->barrier);

  switch (tinfo->action) {
  case ACTION_INSERTION:
    insertions (tinfo->map, tinfo->size);
    break;
  case ACTION_REMOVAL:
    removals (tinfo->map, tinfo->size);
    break;
  case ACTION_RETRIEVAL:
    retrievals (tinfo->map, tinfo->size);
    break;
  }

}

int main (int argc, char *argv[])
{
  hash_map_t *map = NULL;
  struct thread_info *tinfo = NULL;
  pthread_attr_t attr;
  pthread_barrier_t barrier = {0,};
  int ret = -1;
  int tcount = 100, idx = 0;

  map = hash_map_init ();
  if (map == NULL) {
    printf ("failed to initialize hash map\n");
  }

  hh_random_init ();

  ret = pthread_attr_init(&attr);
  if (ret != 0)
    printf ("ERROR: failed to initialize pthread attr\n");

  pthread_barrier_init (&barrier, NULL, tcount + 1);

  tinfo = calloc (tcount, sizeof(struct thread_info));
  if (tinfo == NULL)
    printf ("ERROR: calloc failed\n");

  for (idx = 0; idx < tcount; idx++) {
    tinfo[idx].action = (hh_random() % 3) + 1;

    if (tinfo[idx].action == ACTION_INSERTION)
      tinfo[idx].size = 100 + idx;
    else
      tinfo[idx].size = 23;

    tinfo[idx].map = map;

    tinfo[idx].barrier = &barrier;
  }

  for (idx = 0; idx < tcount; idx++)
    pthread_create (&tinfo[idx].thread_id, &attr, &thread_start, &tinfo[idx]);

  /* tinfo[0].action = ACTION_INSERTION; */
  /* tinfo[0].size = 100; */

  /* tinfo[1].action = ACTION_REMOVAL; */
  /* tinfo[1].size = 20; */

  /* tinfo[2].action = ACTION_RETRIEVAL; */
  /* tinfo[2].size = 20; */

  /* tinfo[0].map = tinfo[1].map = tinfo[2].map = map; */

  /* tinfo[0].barrier = tinfo[1].barrier = tinfo[2].barrier = &barrier; */

  /* //  insertions (map, 100); */
  /* pthread_create (&tinfo[0].thread_id, &attr, &thread_start, &tinfo[0]); */

  /* //  removals (map, 20); */
  /* pthread_create (&tinfo[1].thread_id, &attr, &thread_start, &tinfo[1]); */

  /* //  retrievals (map, 10); */
  /* pthread_create (&tinfo[2].thread_id, &attr, &thread_start, &tinfo[2]); */

  pthread_barrier_wait (&barrier);

  for (idx = 0; idx < tcount; idx++)
    pthread_join (tinfo[idx].thread_id, NULL);


  /* pthread_join (tinfo[0].thread_id, NULL); */
  /* pthread_join (tinfo[1].thread_id, NULL); */
  /* pthread_join (tinfo[2].thread_id, NULL); */

  hash_map_dump (map);

  return 0;
}
