#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main (){

	int pid;
	int fd[2];
	char buf[256];

	printf("Enter string for child:\n");
//	scanf("%s", buf);
	read(0, buf, 256);

	pipe(fd);

	switch(pid = fork()){
		case -1:
			printf("ERROR: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		case 0:
			printf("It's child, pid:%d\n", getpid());
			if (close(fd[0]) == -1){
				printf("ERROR: %s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}
			if (write(fd[1], &buf, strlen(buf)) == -1){
				printf("ERROR: %s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}
			if (close(fd[1]) == -1){
				printf("ERROR: %s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}
			exit(EXIT_SUCCESS);
		default:
			printf("It's parent, pid %d\n", getpid());
			if (close(fd[1]) == -1){
				printf("ERROR: %s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}
			if (read(fd[0], &buf, strlen(buf)) == -1){
				printf("ERROR: %s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}
			printf("%s\n", buf);
			if (close(fd[0]) == -1){
			printf("ERROR: %s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}
			wait(NULL);
			exit(EXIT_SUCCESS);
	}
}
