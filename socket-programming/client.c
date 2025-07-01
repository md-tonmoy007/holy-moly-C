#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "socketutil.h"

void startListeningAndPrintMessagesOnNewThread(int socketFD);
void* listenAndPrint(void* arg);
void readConsoleEntriesAndSendToServer(int socketFD);

int main() {
    int socketFD = createTCPIpv4Socket();
    struct sockaddr_in *address = createIPv4Address("127.0.0.1", 2000);

    int result = connect(socketFD, (struct sockaddr*)address, sizeof(*address));
    if (result == 0) {
        printf("connection established\n");
    } else {
        perror("Failed to connect");
        return 1;
    }

    startListeningAndPrintMessagesOnNewThread(socketFD);

    readConsoleEntriesAndSendToServer(socketFD);
    close(socketFD);
    return 0;
}

void readConsoleEntriesAndSendToServer(int socketFD) {
    char *name = NULL;
    size_t nameSize = 0;
    printf("Enter your name: ");
    ssize_t nameCount = getline(&name, &nameSize, stdin);
    if (nameCount > 0 && name[nameCount - 1] == '\n') {
        name[nameCount - 1] = 0; // Remove newline character
    }

    char *line = NULL;
    size_t lineSize = 0;
    char buffer[1024];

    while (true) {
        printf("Enter your message: ");
        ssize_t charCount = getline(&line, &lineSize, stdin);
        if (charCount <= 0) {
            break;
        }
        if (line[charCount - 1] == '\n') {
            line[charCount - 1] = 0; // Remove newline character
        }

        if (strcmp(line, "exit") == 0) {
            break;
        }

        snprintf(buffer, sizeof(buffer), "%s: %s", name, line);
        ssize_t amountWasSent = send(socketFD, buffer, strlen(buffer), 0);
        if (amountWasSent <= 0) {
            printf("Failed to send message or server disconnected.\n");
            break;
        }
    }

    free(name);
    free(line);
}

void startListeningAndPrintMessagesOnNewThread(int socketFD) {
    pthread_t id;
    int *fdPtr = malloc(sizeof(int));
    *fdPtr = socketFD;
    pthread_create(&id, NULL, listenAndPrint, fdPtr);
    pthread_detach(id);
}

void* listenAndPrint(void* arg) {
    int socketFD = *(int*)arg;
    free(arg);
    char buffer[1024];

    while (true) {
        ssize_t amountReceived = recv(socketFD, buffer, sizeof(buffer) - 1, 0);

        if (amountReceived > 0) {
            buffer[amountReceived] = 0; // Null-terminate the string
            printf("%s\n", buffer);
        }

        if (amountReceived <= 0) {
            printf("Server disconnected.\n");
            break;
        }
    }
    close(socketFD);
    return NULL;
}