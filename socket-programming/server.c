#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {

    int socketFD = createTCPIpv4Socket();
    struct sockaddr_in *address = createIPv4Address("127.0.0.1", 2000);
    char buffer[1024] = {0};

    // Connect to the server
    int result = connect(socketFD, (struct sockaddr*)&address, sizeof(address));
    if (result == 0) {
        printf("Connection was successful\n");
    } else {
        perror("Connection failed");
        return 1;
    }

    // Send HTTP GET request
    char* message = "GET / HTTP/1.1\r\nHost: google.com\r\nConnection: close\r\n\r\n";
    send(socketFD, message, strlen(message), 0);

    // Receive response
    int bytesReceived;
    while ((bytesReceived = recv(socketFD, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytesReceived] = '\0'; // Null-terminate the string
        printf("%s", buffer);
    }

    // Close socket
    close(socketFD);
    return 0;
}
