#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *PrintInt(int num) {
	
	printf("Hello World! It's me, thread #%d!\n", num);
	pthread_exit(NULL);
}
void *PrintChar(char sen) {
	
	
	printf("Hello World! It's me, thread #%c!\n", sen);
	pthread_exit(NULL);
}
int main(int argc, char *argv[]) {
	pthread_t threads[2];
	int rc;
	
	int num = 333;
	char sentence = 'a';
	printf("In main: creating thread 1\n");
	rc = pthread_create(&threads[0], NULL, PrintInt, num);
	if (rc) {
		perror("Failed in calling pthread_create");
		exit(-1);
	}
	printf("In main: creating thread 2\n");
	rc = pthread_create(&threads[1], NULL, PrintChar, sentence);
	if (rc) {
		perror("Failed in calling pthread_create");
		exit(-1);
	}
	
	pthread_exit(NULL);
}
