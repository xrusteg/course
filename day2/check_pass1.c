#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

char password[] = "password";
char str[30];

pthread_cond_t wake_up;
pthread_mutex_t mut;
void *enter_pass()
{
	while(1)
	{
		pthread_mutex_lock(&mut);
		printf("Enter password:\n");
		scanf("%s", str);
		pthread_cond_signal(&wake_up);
		pthread_mutex_unlock(&mut);
		pthread_cond_wait(&wake_up, &mut);
	}
}

void *check_pass()
{
	while(1) {
		pthread_cond_wait(&wake_up, &mut);
		if(!strcmp(str , password)) {
				printf("true\n");
				exit(EXIT_SUCCESS);
		}
		else
			printf("Wrong password, try another\n");
			pthread_cond_signal(&wake_up);
	}
}
	
int main(void)
{
	pthread_t thread1, thread2;
	int rc;

	rc = pthread_create(&thread1, NULL, enter_pass, NULL);
	if (rc) {
		printf("ERROR: %s\n", strerror(errno));
		//exit(EXIT_FAILURE);
	}
	rc = pthread_create(&thread2, NULL, check_pass, NULL);
	if (rc) {
		printf("ERROR: %s\n", strerror(errno));
		//exit(EXIT_FAILURE);
	}

	/*while(1)
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
		}*/
	}

