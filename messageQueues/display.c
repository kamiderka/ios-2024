#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MAX_TEXT 512

struct message {
    long int message_type;
    char username[20];
    char text[MAX_TEXT];
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <username>\n", argv[0]);
        exit(1);
    }

    char *username = argv[1];
    int user_id = 0;
    if (strcmp(username, "user1") == 0) user_id = 0;
    else if (strcmp(username, "user2") == 0) user_id = 1;
    else if (strcmp(username, "user3") == 0) user_id = 2;
    else {
        printf("Invalid username. Choose from user1, user2, user3.\n");
        exit(1);
    }

    int msgid;
    struct message msg;
    key_t key = ftok("chat_server", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);

    printf("Chat client display started for %s. Key: %d\n", username, user_id + 2);
    
    while (1) {
        if (msgrcv(msgid, &msg, sizeof(struct message) - sizeof(long), user_id + 2, 0) != -1) {
            printf("[%s]: %s\n", msg.username, msg.text);
        }
    }

    return 0;
}
