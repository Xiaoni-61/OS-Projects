#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>

#define MAX_TEXT 50

struct msgbuf {
    long mtype;
    char mtext[MAX_TEXT];
};

int main(int argc, char **argv)
{
    int qid;
    struct msgbuf data;
    int msgtype = 110;

    qid = msgget((key_t)0324, 0666 | IPC_CREAT);
    if (qid == -1)
    {
        perror("Failed to create queue");
        return EXIT_FAILURE;
    }

    for(int i = 0; i < 10; i++)
    {
        if (msgrcv(qid, (void *)&data, 50, msgtype, 0) == -1)
        {
            perror("Failed to receive from queue");
        }
		msgtype--;
        printf("%s", data.mtext);
    }

    if (msgctl(qid, IPC_RMID, 0) == -1)
    {
        perror("Failed to destroy queue");
    }

    return EXIT_SUCCESS;
}