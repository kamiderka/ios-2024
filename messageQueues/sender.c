#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MQ_NAME "/chat_queue"
#define MQ_MSGSIZE 1024

struct msg_buffer {
    long msg_type;
    char msg_text[MQ_MSGSIZE];
};

int main(int argc, char *argv[]){

    mqd_t mq;

    struct mq_attr attributes = {
        .mq_flags = 0, 
        .mq_maxmsg = 10,
        .mq_curmsgs = 0, 
        .mq_msgsize = 1024
    };

    mq = mq_open(MQ_NAME, O_WRONLY, 0644, &attributes);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        exit(1);
    }

    printf("Message queue opened successfully.\n");

    char buffer[1024];

    strcpy(buffer, "Hello, Message Queue!");
    if (mq_send(mq, buffer, strlen(buffer) +1, 0) == -1) {
        perror("mq_send");
        exit(1);
    }

    printf("Message sent: %s\n", buffer);




    return 0;
}