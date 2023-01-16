*//This is the server program where the file handling ,storing,and client server relationship takes place along with server operations/
********************************************************************************************************
********************************************************************************************************
** FILENAME : Server.c **
** DESCRIPTION : Implementation of above details **
********************************************************************************************************
********************************************************************************************************
***************************HEADER FILES*****************************************************************

#include <memory.h>
#include <netinet/in.h>                        //INCLUDES THE INTERNET ADRESS FAMILY
#include <stdio.h>                             //INCLUDES THE OUTPUT RELATED FUNCTIONS
#include <stdlib.h>                            //INCLUDES FUNCTIONS INVOLVING MEMORY ALLOCATION,UTILITY FUNCTIONS FOR TYPE CONVERSIONS
#include <string.h>                            //INCLUDES FUNTIONS TO PERFORM STRING OPERATIONS
#include <sys/socket.h>                        //INCLUDES SOCKADDR STRUCTURE 
#include <arpa/inet.h>                         //INCLUDES DEFINITIONS FOR INTERNET OPEARATIONS
int main()
{
    int udpSocket, nBytes;
    char buffer[3000], xor[3000];
    char const key[1024] = "HI DDENKEY";
    struct sockaddr_in serverAddr, clientAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size, client_addr_size;
    

    int i;
    udpSocket = socket(PF_INET, SOCK_DGRAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5004);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
    bind(udpSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    addr_size = sizeof serverStorage;
    puts("Waiting for client :");
    int count = 0;
    while (1) {
        nBytes = recvfrom(udpSocket, buffer, 3000, 0, (struct sockaddr*)&serverStorage,&addr_size);
        printf("Message no : %d\n", ++count);
        for (i = 0; i < nBytes - 1; i++) {
            if (buffer[i] != '\n')
                xor[i] = (char)(buffer[i] ^ key[i]);
            else
                xor[i] = buffer[i];
        }
        printf("Encrypted message stored in file : \n");
        for (i = 0; i< 15; i++)
            printf("%02X ", xor[i]);
        printf("\n");
        FILE* fp;
        

        fp = fopen("temp.txt", "w+");
        for (i = 0; i < nBytes-1; i++) {
            if (xor[i] != '\n')
                fprintf(fp, "%X", xor[i]);
            else
                fprintf(fp, "%c", xor[i]);
        }
        fclose(fp);
        sendto(udpSocket, xor, nBytes, 0, (struct sockaddr*)&serverStorage,addr_size);
    }
    return 0;
}
