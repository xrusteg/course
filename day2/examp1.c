#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 2

int global;

void *glob() {
	int i;
	for (i = 0; i < 10; i++){
		global++;
		printf("GLOB:%d\n", global);
	sleep(1);
	}

}

void *glob1() {
	int i;
	for (i = 0; i < 10; i++){
		global--;
		printf("GLOB1:%d\n", global);
	sleep(1);
	}

}

int main (int argc, char *argv[]) {
  pthread_t threads[NUM_THREADS];
  int rc;
  long t;
  pthread_t n, n1;
	rc = pthread_create(&n, NULL, glob, NULL);
    if (rc) {
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(-1);
    }

	rc = pthread_create(&n1, NULL, glob1, NULL);
    if (rc) {
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(-1);
    }

  
    pthread_join(n, NULL);
    printf("Thread #%ld finished\n", t);

		pthread_join(n1, NULL);
    printf("Thread #%ld finished\n", t);
  

  return 0;
}
