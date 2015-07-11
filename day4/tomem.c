#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <string.h>

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

	in = open("1mb_file", O_RDONLY);
//	out = open("out", O_WRONLY | O_CREAT | O_EXCL, S_IWUSR | S_IRUSR);
	int n;
	n = read(in, shared_memory, shared_segment_size);
	printf("N:%d\n", n);
	//write(out, buf, shared_segment_size);
	
	//n = write(shared_memory, buf, shared_segment_size);
	/*printf("N:%d\n", n);
	if (n == -1) {
		printf("ERROR: %s\n", strerror(errno));
	}*/

	//sprintf (shared_memory, "Hello, world.");
//	strcpy(shared_memory, buf);
//	memcpy(shared_memory, buf, shared_segment_size);
	shmdt (shared_memory);
}
