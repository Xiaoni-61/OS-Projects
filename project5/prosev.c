#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<errno.h>

#define MAX_LEN 5

int buf[MAX_LEN];
int in, out;

sem_t empty, full, mutex;

void *produce(void *p);
void *consume(void *p);
void init_semaphore(sem_t *sem, int init_value, char *sem_name);

int main(int argc, char **argv)
{
	pthread_t tid[4];
	pthread_attr_t attr;
	int i;
	int result;
	int consumer_id[2] = {0, 1};
	if (argc != 3)
	{
		printf("enter 2 parameter2");
		exit(0);
	}
	
	init_semaphore(&empty, MAX_LEN, "empty");
	init_semaphore(&full, 0, "full");
	init_semaphore(&mutex, 1, "mutex");
	
	in = out = 0;
	
	pthread_attr_init(&attr);
	
	for(i = 0; i < 2; i++)
	{
		result = pthread_create(&(tid[i]), &attr, produce, (void *)argv[1 + i]);
		if (result)
		{
			perror("Error creating producer!");
			exit(1);
		}
	}
	
	for(i = 0; i < 2; i++)
	{
		result = pthread_create(&(tid[i+2]), &attr, consume, (void *)(&consumer_id[i]));
		if (result)
		{
			perror("Error creating consumer!");
			exit(1);
		}
	}
	
	for(i = 0; i < 4; i++ )
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

void *produce(void *p)
{
	FILE *fp;
	int i;
	int value;
	int result;
	
	printf("File name: %s\n", (char *)p);
	
	fp = fopen((char *)p, "r");
	
	if (fp == NULL)
	{
		perror("Can not open file");
		printf("File name: %s\n",(char *)p);
		exit(1);
		
	}
	for(i == 0; i < 10; i++)
	{
		result = fscanf(fp, "%d", &value);
		if (result != 1)
		{
			printf("Read error.\n");
			exit(1);
			
		}
		printf("Reading %d\n",value);
		
		sem_wait(&empty);
		sem_wait(&mutex);
		
		buf[in++] = value;
		in %= MAX_LEN;
		
		sem_post(&mutex);
		sem_post(&full);
		
	}
	fclose(fp);
	pthread_exit((void *)NULL);
}

void *consume(void *p)
{
	int i,j;
	int values[2];
	int result;
	char op;
	
	for (i = 0;i < 5; i++)
	{
		for (j = 0; j < 2; j++)
		{
			sem_wait(&full);
			sem_wait(&mutex);
			
			values[j] = buf[out++];
			out %=MAX_LEN;
			
			sem_post(&mutex);
			sem_post(&empty);
		}
		
		if (*((int *)p) == 0)
		{
			op = '+';
			result = values[0] + values[1];
		}
		else
		{
			op = '*';
			result = values[0] * values[1];
		}
		printf("%d %c %d = %d",values[0],op,values[1],result);
		
	}
	pthread_exit((void *)NULL);
}

