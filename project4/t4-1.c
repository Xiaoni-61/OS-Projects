#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NUM_THREADS 2
void *myThread1(void *threadid) {
	long tid;
	tid = (long) threadid;
	printf("Hello World! It's me, thread!\n");
	pthread_exit(NULL);
}
void *myThread2(void *threadid) {
	long tid;
	tid = (long) threadid;
	printf("This is my dream!\n");
	pthread_exit(NULL);
}
int main(int argc, char *argv[]) {
	pthread_t threads[NUM_THREADS];
	int rc;
	long t;
	for (t = 0; t < NUM_THREADS; t++) {
		printf("In main: creating thread %ld\n", t);
		if(t==0){
			rc = pthread_create(&threads[t], NULL, myThread1, (void *) t);
		}
		if(t==1){
			rc = pthread_create(&threads[t], NULL, myThread2, (void *) t);
		}
		
		if (rc) {
			perror("Failed in calling pthread_create");
			exit(-1);
		}
	}
	pthread_exit(NULL);
}
