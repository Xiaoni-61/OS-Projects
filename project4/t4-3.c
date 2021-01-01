#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


typedef struct bicomplex{
    int real1;
    int real2;
    int plurality1;
    int plurality2;
}Bicomplex;


typedef struct add{
    int real;
    int plurality;
}Add;


void *calculate(void *num) {
	
	Bicomplex *rnum;
	Add *ans = (Add *)malloc(sizeof(Add));
	rnum=(Bicomplex *)num;
	ans->real = rnum->real1 + rnum->real2;
	ans->plurality = rnum->plurality1 + rnum->plurality2;
	pthread_exit((void *)ans);
}

int main(int argc, char *argv[]) {
	pthread_t threads;
	int rc;
	
	Bicomplex num;
	Add *a;
	void *ans;
	num.real1 = 1;
	num.real2 = 2;
	num.plurality1 = 1;
	num.plurality2 = 2;	


	printf("In main: creating thread 1\n");
	rc = pthread_create(&threads, NULL, calculate, &num);
	if (rc) {
		perror("Failed in calling pthread_create");
		exit(-1);
	}
	
	pthread_join(threads, &ans);
	a = (Add *)ans;
	printf("The ans is %d + i%d", a->real, a->plurality);
	return 0;
}
