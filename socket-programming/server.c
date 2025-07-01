#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdbool.h>
#include <pthread.h>

#include "socketutil.h"

struct AcceptedSocket {
    int acceptedSocketFD;
    struct sockaddr_in address;
    int error;
    bool acceptedSuccessfully;
};

struct AcceptedSocket* acceptIncomingConnection(int serverSocketFD);
void startAcceptingIncomingConnections(int serverSocketFD);
void* receiveAndPrintIncomingData(void* arg);
void receiveAndPrintIncomingDataOnSeperateThread(struct AcceptedSocket *pSocket);
void sendReceiveMessageToTheOtherClients(char *buffer, int socketFD);

struct AcceptedSocket acceptedSockets[10];
int acceptedSocketCount = 0;

void startAcceptingIncomingConnections(int serverSocketFD){
    while (true) 
    {
        struct AcceptedSocket* clientSocket = acceptIncomingConnection(serverSocketFD);
        acceptedSockets[acceptedSocketCount++] = *clientSocket;
        receiveAndPrintIncomingDataOnSeperateThread(clientSocket);
    }
}

void receiveAndPrintIncomingDataOnSeperateThread(struct AcceptedSocket *pSocket) {
    pthread_t id;
    // Pass pointer to acceptedSocketFD as argument
    int *fdPtr = malloc(sizeof(int));
    *fdPtr = pSocket->acceptedSocketFD;
    pthread_create(&id, NULL, receiveAndPrintIncomingData, fdPtr);
    pthread_detach(id); // Detach thread to reclaim resources automatically
}

void* receiveAndPrintIncomingData(void* arg) {
    int socketFD = *(int*)arg;
    free(arg); // Free the memory allocated for the socketFD
    char buffer[1024];

    while (true)
    {
        ssize_t amountReceived = recv(socketFD, buffer, 1024, 0);

        if (amountReceived > 0)
        {
            buffer[amountReceived] = 0;
            printf("%s\n", buffer);

            sendReceiveMessageToTheOtherClients(buffer, socketFD);
        }
        if (amountReceived == 0 || amountReceived == -1)
        {
            break;
        }
    }
    close(socketFD);
    return NULL;
}

void sendReceiveMessageToTheOtherClients(char *buffer, int socketFD) {
    for (int i = 0; i < acceptedSocketCount; i++)
    {
        if (acceptedSockets[i].acceptedSocketFD != socketFD) {
            send(acceptedSockets[i].acceptedSocketFD, buffer, strlen(buffer), 0);
        }
    }
}

struct AcceptedSocket* acceptIncomingConnection(int serverSocketFD) {
    struct sockaddr_in clientAddress;
    socklen_t clientAddressSize = sizeof(struct sockaddr_in);
    int clientSocketFD = accept(serverSocketFD, (struct sockaddr*)&clientAddress, &clientAddressSize);

    struct AcceptedSocket *acceptedSocket = malloc(sizeof(struct AcceptedSocket));
    acceptedSocket->address = clientAddress;
    acceptedSocket->acceptedSocketFD = clientSocketFD;
    acceptedSocket->acceptedSuccessfully = clientSocketFD > 0;

    if (!acceptedSocket->acceptedSuccessfully)
    {
        acceptedSocket->error = clientSocketFD;
    }

    return acceptedSocket;
}

int main() {
    int serverSocketFD = createTCPIpv4Socket();
    struct sockaddr_in *serverAddress = createIPv4Address("", 2000);

    int result = bind(serverSocketFD, (struct sockaddr*)serverAddress, sizeof(*serverAddress));
    if (result == 0)
    {
        printf("Server bound to port 2000\n");
    }
    else
    {
        perror("Failed to bind server socket");
        return 1;
    }

    int listenResult = listen(serverSocketFD, 10);
    if (listenResult != 0) {
        perror("Failed to listen on server socket");
        return 1;
    }
    startAcceptingIncomingConnections(serverSocketFD);
    shutdown(serverSocketFD, SHUT_RDWR);
    return 0;
}