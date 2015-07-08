#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>


struct out {
	char data[1024];
	char name[1024];
};

struct out outs[32];

int main() {
  int fd[2];
  pid_t pid;
  char foo[4096];
  char buf[1];
  char tmp[256];
	char delim[] = "";
	char *ptr;
	char temp[64];
	int i, j, n, k;
	struct out *ptrl;
	
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
	j = 0;
	while (read(fd[0], &foo[i], 1)){
		
//		printf("%s", &foo[i]);
		if ((foo[i] == '\n') || (foo[i] == '\0')){
			//ptrl = (struct out *) malloc(sizeof(struct out));
			strcpy(tmp, foo);
//			outs[j].data = tmp;
			strcpy(outs[j].data, tmp);
//			printf("%s", outs[j].data);
//			printf("%s", tmp);
		  //ptr = strrchr(tmp, ' ');
		  //memset(outs[j].name, 0, sizeof(outs[j].name));
 			//strcpy(outs[j].name, ptr+1);
//			printf("!%s", outs[j].name);
//		  printf("%s", ptr+1);
// 			printf("%s", tmp);
			//strcpy(outs[j].data, tmp);
			memset(foo, 0, sizeof(foo));
			memset(tmp, 0, sizeof(tmp));
			j++;
			i = 0;
			continue;
		}
		i++;
	}
//				printf("%s", outs[2].name);
	
	n = j;
	/*strcpy(temp, outs[1].data);
	strcpy(outs[1].data, outs[2].data);
  strcpy(outs[2].data, temp);*/
	for (i = 0; i < n; i++)
//			printf("%s", outs[i].data);
			

	for (i = 0; i < n; i++) {
      for (j = 0; j < n - 1; j++) {
	      if (strcmp((strrchr(outs[j].data, ' ')), strrchr(outs[j+1].data, ' ')) < 0) {
	      	strcpy(temp, outs[j].data);
					strcpy(outs[j].data, outs[j+1].data);
          strcpy(outs[j+1].data, temp);
         }
       }
  }
	for (i = 0; i < n; i++)
			printf("%s", outs[i].data);
	
	
	
	/*n = j;
	strcpy(temp, outs[1].name);
	strcpy(outs[1].name, outs[2].name);
  strcpy(outs[2].name, temp);
	printf("%d", strcmp(outs[1].name, outs[2].name));
  for (i = 0; i < n; i++)
			printf("%s", outs[i].name);
	n = j;
	for (i = 0; i < n; i++) {
      for (j = 0; j < n - 1; j++) {
         if (strcmp(outs[j].name, outs[j+1].name) > 0) {
         		printf("ERWR");
         		strcpy(temp, outs[j].name);
            strcpy(outs[j].name, outs[j+1].name);
            strcpy(outs[j+1].name, temp);
  //          for (k = 0; k < n; k++)
//						printf("%s", outs[k].data);
						
         }
      }
   }

   for (i = 0; i < n; i++)
			printf("%s", outs[i].name);*/
//	printf("%d", strcmp(outs[0].name, outs[1].name));
//	printf("%s", foo);
	//printf("Output: (%.*s)\n", nbytes, foo);
		wait(NULL);
		exit(EXIT_SUCCESS);
  }
  

  
  return 0;
}

