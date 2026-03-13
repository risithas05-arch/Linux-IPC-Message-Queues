//To implement the communication between  two processes using message queues API using C programming
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main(int argc, char *argv[]) {

    key_t key = 0x41263233;
    int msgid;

    struct msg_buffer message;

    msgid = msgget(key, 0666 | IPC_CREAT);

    if (strcmp(argv[1], "writer") == 0) {

        printf("Enter Message: ");
        fgets(message.msg_text, 100, stdin);

        message.msg_type = 1;

        msgsnd(msgid, &message, sizeof(message), 0);

        printf("Message sent: %s", message.msg_text);
    }

    else if (strcmp(argv[1], "reader") == 0) {

        msgrcv(msgid, &message, sizeof(message), 1, 0);

        printf("Message received: %s", message.msg_text);
    }

    return 0;
}