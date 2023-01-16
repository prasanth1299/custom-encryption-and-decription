#include <memory.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
int clientSocket, portNum, nBytes;
char file_buffer[3000], path[1024], buffer[3000];
char const key[3000] = "HIDDENKEY";
struct sockaddr_in serverAddr;
socklen_t addr_size;
int i;