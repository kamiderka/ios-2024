#include <stdio.h>

int main(int argc, char *argv[]){

    if (argc != 2) {
        printf("Usage: %s <reciever_name>\n", argv[0]);
        return 1;
    }

    char *recieverName = argv[1];

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), stdin) != NULL ) {
        printf("%s: %s", recieverName,  buffer); 
    }

    return 0;
}