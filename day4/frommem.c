#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/ipc.h>

#define KEY ((key_t)(123))
#define shared_segment_size 1048576


int main () {
	int segment_id, in, out;
	char* shared_memory;
	struct shmid_ds shmbuffer;
	char buf[shared_segment_size];

	segment_id = shmget (KEY, shared_segment_size, 0666 | IPC_CREAT);
	if (segment_id == -1) {
		printf("ERROR: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	shared_memory = (char*) shmat (segment_id, 0, 0);
	printf ("shared memory attached at address %p\n", shared_memory);

//	in = open("1mb_file", O_RDONLY);
	out = open("out", O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);
	
	//read(in, buf, shared_segment_size);
	//write(out, buf, shared_segment_size);
	int n;
	
	n = write(out, shared_memory, shared_segment_size);
	printf("N:%d\n", n);
	if (n == -1) {
		printf("ERROR: %s\n", strerror(errno));
	}

//	sprintf (shared_memory, "Hello, world.");
	close(out);

	shmdt (shared_memory);
}
