
#ifndef Server_h
#define Server_h

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

struct Server {
    int domain;
    int service;
    int protocol;
    u_long interface;
    int port;
    int backlog;


    struct sockaddr_in address;
};

 



#endif