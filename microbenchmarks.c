#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/mman.h>
#include "statistics.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define NANOSECONDS_PER_SECOND 1E9
#define N_REPS 50000
#define NUM_SPECS 3

void *childfunc(void *offset)
{
  return NULL;
}

/* malloc_shared acts like malloc in that it will allocate and return size bytes of memory,
   but it will also ensure that this region of memory is shared with all child processes.
   NOTE: it will NOT be guarded by any synchronization primitives, so you need to make sure only one
   of the parent or child is accessing it at any given time. Pro-tip: you can use exit() in the child
   and wait() in the parent in a way similar to the barriers in homework 6 to ensure only one process
   is accessing it at any given time.
   */
void * malloc_shared(size_t size){
   return mmap(NULL,size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);
}

void test_threads(){
  pthread_t child;
  for (long i = 0; i < N_REPS; i++)
  {
    pthread_create(&child, NULL, childfunc, (void *)i);
    pthread_join(child, NULL);
  }
}

void test_processes(){
  int wpid, status, retval;

  for (int i = 0; i < N_REPS; i++) {
    retval = fork();
    if(retval == 0){
      exit(0);
    }
    else{
      // do nothing
    }
    wpid = wait(&status);
  }
  // wait for all worker processes to finish
  while ((wpid = wait(&status)) > 0);
}


int main(int argc, char **argv)
{
  printf("spawning a lot of threads.\n");
  test_threads();
  printf("spawning a lot of processes.\n");
  test_processes();
  return EXIT_SUCCESS;
}
