#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "socketutil.h"

int main() {
    int socketFD = createTCPIpv4Socket();
    struct sockaddr_in *address = createIPv4Address("142.250.192.78", 80);
    char buffer[1024] = {0};

    int result = connect(socketFD, (struct sockaddr*)address, sizeof(struct sockaddr_in));
    if (result == 0) {
        printf("Connection was successful\n");
    } else {
        perror("Connection failed");
        return 1;
    }

    char* message = "GET / HTTP/1.1\r\nHost: google.com\r\nConnection: close\r\n\r\n";
    send(socketFD, message, strlen(message), 0);

    int bytesReceived;
    while ((bytesReceived = recv(socketFD, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytesReceived] = '\0';
        printf("%s", buffer);
    }

    close(socketFD);
    free(address);  // free allocated memory
    return 0;
}
