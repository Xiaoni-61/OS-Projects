#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(){
	
	pid_t result1;

	printf("Original\n");

	result1=fork();

	if (result1 < 0) {
		perror("Failed to create process after <A>");
 		exit(1);
 	}
	else if(result1==0){
		printf("Child 1\n");
	}
	else{
		printf("Parents\n");
		result1=fork();
		if (result1 < 0) {
                	perror("Failed to create process after <A>");
                	exit(1);
        	}
		else if(result1==0){
	                printf("Child 2\n");
        	}
		else{
			exit(1);
		}


	}





}
