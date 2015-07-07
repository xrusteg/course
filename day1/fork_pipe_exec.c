#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>


struct out {
	char data;
	char name;
};

int main() {
  int fd[2];
  pid_t pid;
  char foo[4096];
  char buf[1];
  char tmp[256];
	char delim[] = "";
	char *ptr;
	int i;
	
  if (pipe(fd)==-1){
  	printf("ERROR: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
  if ((pid = fork()) == -1){
			printf("ERROR: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
	}
  if(pid == 0) {

    dup2 (fd[1], STDOUT_FILENO);
    close(fd[0]);
    close(fd[1]);
    execl("/bin/ls", "ls", "-l", "/tmp", (char *)0);
		printf("ERROR: %s\n", strerror(errno));
		exit(EXIT_FAILURE);

  } else {

	close(fd[1]);
	//int nbytes = 
	i = 0;
	while (read(fd[0], &foo[i], 1)){
		
//		printf("%s", &foo[i]);
		if ((foo[i] == '\n') || (foo[i] == '\0')){
			strcpy(tmp, foo);
			printf("%s", tmp);
		  ptr = strrchr(tmp, ' ');
		  printf("%s\n", ptr+1);
			memset(foo, 0, sizeof(foo));
			memset(tmp, 0, sizeof(tmp));
			i = 0;
			continue;
		}
		i++;
	}
//	printf("%s", foo);
	//printf("Output: (%.*s)\n", nbytes, foo);
		wait(NULL);
		exit(EXIT_SUCCESS);
  }
  

  
  return 0;
}

