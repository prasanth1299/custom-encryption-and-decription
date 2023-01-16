#include <memory.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
int main()
{
    int udpSocket, nBytes;
    char buffer[3000], xor[3000];
    char const key[1024] = "HI DDENKEY";
    struct sockaddr_in serverAddr, clientAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size, client_addr_size;
    

    int i;
