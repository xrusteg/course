#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

char password[] = "password";
char str[30];

pthread_cond_t wake_up;
pthread_mutex_t mut;

void *enter_pass(void *a)
{

  while(1)
    {
      printf("Enter password:\n");
      scanf("%s", str);

      pthread_mutex_lock(&mut);
      pthread_cond_signal(&wake_up);
      pthread_mutex_unlock(&mut);
    }
}

void *check_pass(void *a)
{
  while(1) {
    pthread_mutex_lock(&mut);
    pthread_cond_wait(&wake_up, &mut);
    pthread_mutex_unlock(&mut);
    if(!strcmp(str , password)) {
      printf("true\n");
      exit(EXIT_SUCCESS);
    }
    printf("Wrong password, try another\n");
  }
}


int main(void)
{
  pthread_t thread1, thread2;

  pthread_mutex_init(&mut, NULL);
  pthread_cond_init (&wake_up, NULL);
  pthread_create(&thread1, NULL, enter_pass, 0);
  pthread_create(&thread2, NULL, check_pass, 0);
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  exit(EXIT_SUCCESS);
}

