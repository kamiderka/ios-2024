#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MQ_NAME "/chat_queue"
#define MQ_MSGSIZE 1024


int main(int argc, char *argv[]){

    mqd_t mq;

    struct mq_attr attributes = {
        .mq_flags = 0, 
        .mq_maxmsg = 10,
        .mq_curmsgs = 0, 
        .mq_msgsize = MQ_MSGSIZE
    };

    mq = mq_open(MQ_NAME, O_CREAT | O_RDWR, 0644, &attributes);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        exit(1);
    }

    printf("Message queue created/opened successfully.\n");

    


    return 0;
}