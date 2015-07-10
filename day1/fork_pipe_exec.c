#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define BUFF_SIZE 1024
#define SIZE_STRS 32

struct out {
	char data[BUFF_SIZE];
};

struct out outs[SIZE_STRS];

int main(void)
{
	int fd[2];
	pid_t pid;
	char foo[4*BUFF_SIZE];
	char *ptr;
	char temp[BUFF_SIZE];
	int i, j, n, k;

	if (pipe(fd) == -1) {
		printf("ERROR: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1) {
			printf("ERROR: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
	}
	if (pid == 0) {
		close(fd[0]);
		dup2(fd[1], 1);
		dup2(fd[1], 2);
		close(fd[1]);
		if (execl("/bin/ls", "ls", "-l", "/tmp", (char *)0) == -1) {
			printf("ERROR: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
	} else {
		close(fd[1]);
		i = 0;
		j = 0;
		while (read(fd[0], &foo[i], 1)) {
			if ((foo[i] == '\n') || (foo[i] == '\0')) {
				strcpy(outs[j].data, foo);
				memset(foo, 0, sizeof(foo));
				j++;
				i = 0;
				continue;
			}
			i++;
		}

		n = j;
		/*strcpy(temp, outs[1].data);
		strcpy(outs[1].data, outs[2].data); //exchange to test
	  strcpy(outs[2].data, temp);
		for (i = 0; i < n; i++)
			printf("%s", outs[i].data);*/

		for (i = 0; i < n; i++) {
			for (j = 0; j < n - 1; j++) {
	      if (strcmp((strrchr(outs[j].data, ' ')), strrchr(outs[j+1].data, ' ')) > 0) { //to sort desc: < 0
					strcpy(temp, outs[j].data);
					strcpy(outs[j].data, outs[j+1].data);
					strcpy(outs[j+1].data, temp);
				}
			}
		}
		for (i = 0; i < n; i++)
			printf("%s", outs[i].data);

		wait(NULL);
		exit(EXIT_SUCCESS);
  }
  exit(EXIT_SUCCESS);
}

