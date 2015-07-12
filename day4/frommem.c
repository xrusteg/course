#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include "bin_sem.h"

#define KEY ((key_t)(123))
#define shared_segment_size 1048576


int main () {
	int segment_id, in, out;
	char* shared_memory;
	struct shmid_ds shmbuffer;
	char buf[shared_segment_size];
	
	key_t key = ftok("100mb_file", 1);
	key_t key1 = ftok("tomem.c", 1);
	
	int semid = binary_semaphore_allocation(key, 0666 | IPC_CREAT);
	//printf("SEMID:%d\n", semid);
	binary_semaphore_initialize(semid);
	
	int semid1 = binary_semaphore_allocation(key1, 0666 | IPC_CREAT);
	binary_semaphore_initialize(semid1);

	segment_id = shmget (KEY, shared_segment_size, 0666 | IPC_CREAT);
	if (segment_id == -1) {
		printf("ERROR: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	shared_memory = (char*) shmat (segment_id, 0, 0);
	printf ("shared memory attached at address %p\n", shared_memory);


	out = open("out", O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);
//	sleep(1);
	int n, i = 0;
	
	for (n = 0; n < 104857600; n+=1048576) {
		binary_semaphore_take(semid);
		binary_semaphore_take(semid1);
		printf("2: %d\n", i);
		i++;
		write(out, shared_memory, shared_segment_size);
		binary_semaphore_free(semid);
		binary_semaphore_free(semid1);
	}
	
	close(out);

	shmdt (shared_memory);
}
