#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

#define INPUT 0
#define OUTPUT 1

int file_descriptors1[2];
int read_count;
char buf[256];

void int_handler()
{
    	close(file_descriptors1[OUTPUT]);
	read_count = read(file_descriptors1[INPUT], buf, sizeof(buf));
	if (read_count == -1) {
		perror("failed to read from");
		exit(1);
	} else if (read_count == 0) {
		printf("0 byte read from pipe.\n");
	} else {
		// read_count > 0
		printf("data: %s\n",buf);
	}
}
int main() {
	
	
	pid_t p1,p2; // process ID
	
	int result;
	char word;
	char *wordip;
	
	int i;
	
	result = pipe(file_descriptors1);
	
	if (result == -1) {
		
		perror("Failed in calling pipe");
		exit(1);
	}

	p1 = fork(); 
	if (p1 < 0) {
		perror("Failed in calling fork");
		exit(1);
	} else if (p1 == 0) {
		sigset( SIGUSR1, int_handler );
		printf("In the P1 process...\n");
		for ( ; ; )
			pause();
		
	} else {
		
		printf("In the parent process...\n");
		p2 = fork();
		if (p2 < 0){
			perror("Failed in calling fork");
			exit(1);
		}
		else if(p2 == 0){
			printf("In the P2 process...\n");
			
			close(file_descriptors1[INPUT]);
			for (i=0;i<20;i=i+1)
			{
				scanf("%c",&word);
				*wordip=word;
				result = write(file_descriptors1[OUTPUT], wordip, 1);
				sleep(0.1);
				if (result == -1) {
					perror("In Child1, failed to write to pipe");
					exit(1);
				}
				if(i%2==0)
				{
					kill(p1,SIGUSR1);
				}
				
			}
			exit(0);
			
		}
		else{
			wait(NULL);
			kill(p1,SIGINT);
			close(file_descriptors1[INPUT]);
			
		}
		
		
	}
	return (EXIT_SUCCESS);
}



