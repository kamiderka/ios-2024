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
    if (argc != 3) {
        printf("Usage: %s <username> <key>\n", argv[0]);
        exit(1);
    }

    char *username = argv[1];
    int key = atoi(argv[2]);

    int msgid;
    struct message msg;
    key_t ipc_key = ftok("chat_server", 65);
    msgid = msgget(ipc_key, 0666 | IPC_CREAT);

    printf("Chat client send started for %s.\n", username);

    msg.message_type = 1;
    strcpy(msg.username, username);

    while (1) {
        fgets(msg.text, MAX_TEXT, stdin);
        msg.text[strcspn(msg.text, "\n")] = '\0'; // Remove newline character
        if (msgsnd(msgid, &msg, sizeof(struct message) - sizeof(long), 0) == -1) {
            perror("msgsnd");
        }
    }

    return 0;
}
