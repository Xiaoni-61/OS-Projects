#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MAX_TEXT 50

struct msgbuf {
    long mtype;
    char mtext[MAX_TEXT];
};

int main(void){
    int qid;
    struct msgbuf wrbuf;
    
    qid = msgget((key_t)0324, IPC_CREAT | 0666);
    if(qid == -1){
        perror("Failed in calling msgget");
        return (-1);
    }
	int i;
    for(i = 101; i < 111; i++){
		gets(wrbuf.mtext);
		
        wrbuf.mtype = i;
        if (msgsnd(qid, (void *)&wrbuf, MAX_TEXT, 0) == -1)
        {
            fprintf(stderr, "msgsnd failed\n");
            exit(EXIT_FAILURE);
        }
    }
    sleep(1);
    return EXIT_SUCCESS;
}
