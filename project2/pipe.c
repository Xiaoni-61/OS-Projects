#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define INPUT 0
#define OUTPUT 1

int main() {
	int file_descriptors1[2];
	int file_descriptors2[2];
	pid_t pid,pid1; // process ID

	char *msg1 = "Child 1 is sending a message!"; // message to send
	char *msg2 = "Child 2 is sending a message!"; // message to send
	char buf[256]; // buffer to store the message
	int read_count;
	int result;

	/* to create a pipe */
	result = pipe(file_descriptors1);
	// file_descriptors[INPUT] for read end of the pipe
	// file_descriptors[OUTPUT] for write end of the pipe
	if (result == -1) {
		// fail to create pipe
		perror("Failed in calling pipe");
		exit(1);
	}

	pid = fork(); // to create a child process
	if (pid < 0) {
		perror("Failed in calling fork");
		exit(1);
	} else if (pid == 0) {
		/* the child process */
		
		
		
		printf("In the child 1 process...\n");
		// to close the input end of the pipe and
		// write a message to the output end
		close(file_descriptors1[INPUT]);

		result = write(file_descriptors1[OUTPUT], msg1, strlen(msg1));
		if (result == -1) {
			perror("In Child1, failed to write to pipe");
			exit(1);
		}
		
		close(file_descriptors1[OUTPUT]);
		exit(0);
	} else {
		/* the parent process */
		printf("In the parent process...\n");
		// to close the output end and
		// read from the input end
		pid1 = pipe(file_descriptors2);
		if(pid1 < 0){
			perror("Failed in calling fork");
			exit(1);
		}
		pid1 = fork();
		if (pid1 < 0){
			perror("Failed in calling fork");
			exit(1);
		}
		else if(pid1 == 0){
			printf("In the child 2 process...\n");
			// to close the input end of the pipe and
			// write a message to the output end
			close(file_descriptors2[INPUT]);

			result = write(file_descriptors2[OUTPUT], msg2, strlen(msg2));
			if (result == -1) {
				perror("In Child1, failed to write to pipe");
				exit(1);
			}
		}
		else{
			close(file_descriptors1[OUTPUT]);

			read_count = read(file_descriptors1[INPUT], buf, sizeof(buf));
			if (read_count == -1) {
				perror("In parent, failed to read from");

				exit(1);
			} else if (read_count == 0) {
				printf("In parent, 0 byte read from pipe.\n");
			} else {
				// read_count > 0
				buf[read_count] = '\0'; // set the end of string
				printf("%d bytes of data received from spawned process: %s\n",
				read_count, buf);
			}
			
			close(file_descriptors2[OUTPUT]);

			read_count = read(file_descriptors2[INPUT], buf, sizeof(buf));
			if (read_count == -1) {
				perror("In parent, failed to read from");

				exit(1);
			} else if (read_count == 0) {
				printf("In parent, 0 byte read from pipe.\n");
			} else {
				// read_count > 0
				buf[read_count] = '\0'; // set the end of string
				printf("%d bytes of data received from spawned process: %s\n",
				read_count, buf);
			}

		close(file_descriptors1[INPUT]);
		close(file_descriptors2[INPUT]);
		}
		
		
	}
	return (EXIT_SUCCESS);
}
