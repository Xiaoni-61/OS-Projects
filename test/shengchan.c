#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<errno.h>



int buf[MAX_LEN];
int in, out;

sem_t a,b,e,c,f;

void *produce(void *p);
void *consume(void *p);
void init_semaphore(sem_t *sem, int init_value, char *sem_name);

int main(int argc, char **argv)
{
	pthread_t tid[6];
	pthread_attr_t attr;
	int i;
	int result;
	int consumer_id[2] = { 1,2,3,4,5,6};
	if (argc != 3)
	{
		printf("enter 2 parameter2");
		exit(0);
	}
	
	init_semaphore(&a, 0, "a");
	init_semaphore(&b, 0, "b");
	init_semaphore(&e, 0, "e");
	init_semaphore(&c, 0, "c");
	init_semaphore(&f, 0, "f");
	
	in = out = 0;
	
	pthread_attr_init(&attr);
	
	
	
	for(i = 0; i < 6; i++)
	{
		result = pthread_create(&(tid[i]), &attr, consume, (void *)(&consumer_id[i]));
		if (result)
		{
			perror("Error creating consumer!");
			exit(1);
		}
	}
	
	for(i = 0; i < 6; i++ )
	{
		pthread_join(tid[i], (void**)NULL);
	}
	return 0;
	
}

void init_semaphore(sem_t *sem_p, int init_value, char *sem_name)
{
	int result;
	result = sem_init(sem_p, 0, init_value);
	 
	if (result)
	{
		perror("Init error mutex");
		printf("Semaphore name: &s\n", sem_name);
		exit(1);
		
	}	
}

void *consume(void *p)
{
	
	
	
	
		
	if (*((int *)p) == 1)
	{
		printf("This is A!\n");
		sem_post(&a);
		sem_post(&a);
	}
	else if (*((int *)p) == 2)
	{
		sem_wait(&a);
		printf("This is B\n");
		sem_post(&b);
	}
	else if (*((int *)p) == 3)
	{
		sem_wait(&b);
		sem_wait(&e);
		printf("This is C\n");
		sem_post(&c);
	}
	else if (*((int *)p) == 4)
	{
		sem_wait(&c);
		sem_wait(&f);
		printf("This is D\n");
		
	}
	else if (*((int *)p) == 5)
	{
		sem_wait(&a);
		printf("This is E\n");
		sem_post(&e);
	}
	else
	{
		sem_wait(&e);
		printf("This is f\n");
		sem_post(&f);
	}
	
		
	
	pthread_exit((void *)NULL);
}

