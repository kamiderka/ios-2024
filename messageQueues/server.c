#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MAX_TEXT 512
#define MAX_USERS 3

struct message {
    long int message_type;
    char username[20];
    char text[MAX_TEXT];
};

int main() {
    int msgid;
    struct message msg;
    key_t key = ftok("chat_server", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);
    
    printf("Chat server started...\n");
    
    while (1) {
        if (msgrcv(msgid, &msg, sizeof(struct message) - sizeof(long), 1, 0) != -1) {
            printf("Received message from %s: %s\n", msg.username, msg.text);
            for (int i = 0; i < MAX_USERS; i++) {
                msg.message_type = 2 + i;
                msgsnd(msgid, &msg, sizeof(struct message) - sizeof(long), 0);
            }
        }
    }
    
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
