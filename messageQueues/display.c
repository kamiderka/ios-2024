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
        .mq_msgsize = MQ_MSGSIZE
    };

    mq = mq_open(MQ_NAME, O_RDONLY, 0644, &attributes);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        exit(1);
    }

    printf("Message queue opened successfully.\n");

    struct msg_buffer message;
    unsigned int priority;

    ssize_t bytes_read = mq_receive(mq, (char *)&message.msg_text, attributes.mq_msgsize, &priority);
    if (bytes_read == -1) {
        perror("mq_receive");
        exit(1);
    }

    printf("Received message: %s\n", message.msg_text);



    return 0;
}