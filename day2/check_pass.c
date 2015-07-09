#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

char password[] = "password";
char str[30];

pthread_cond_t wake_up;

void *enter_pass()
{
	printf("Enter password:\n");
	scanf("%s", str);
	//pthread_cond_signal(&wake_up);
	pthread_exit(NULL);
}
/*
void *check_pass()
{*/
	

int main(void)
{
	pthread_t thread1;
	int rc;

	rc = pthread_create(&thread1, NULL, enter_pass, NULL);
	if (rc) {
		printf("ERROR: %d\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	while(1)
	{
		pthread_join(thread1, NULL);
		if(!strcmp(str , password)) {
			printf("true\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			printf("Wrong password, try another\n");
			rc = pthread_create(&thread1, NULL, enter_pass, NULL);
		}
	}
}
