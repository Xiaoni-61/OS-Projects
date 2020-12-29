#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void){
    char command[255];
    while(1) {
        int result, length, mode = 0, arg_num = 0, t = 1;
        fgets(command, 255, stdin);
        if(strcmp(command, "quit\n") == 0)
            break;
        result = fork();
        if (result < 0) {
            perror("Failed to create child");
            exit(1);
        }
        else if (result == 0) {
            // Child
            length = (int) strlen(command) - 1;
            command[length] = '\0';
            for (int j = 0; j < length; j++) {
                if (command[j] == 32 || command[j] == 9) {
                    arg_num++;
                    command[j] = '\0';
                }
            }
            
			char **coms = (char **) malloc((arg_num + 2) * sizeof(char *));
			coms[0] = " ";
			for (int j = 0; j < length; j++) {
				if (command[j] == '\0') {
					coms[t++] = &command[j + 1];
				}
			}
			coms[arg_num + 1] = NULL;
			result = execvp(command, coms);
			if (result == -1) {
				perror("In child process, failed to exec a program");
				exit(1);
			}
            
            return EXIT_SUCCESS;
        }
        else    //parent
            wait(NULL);
    }
    return EXIT_SUCCESS;
}