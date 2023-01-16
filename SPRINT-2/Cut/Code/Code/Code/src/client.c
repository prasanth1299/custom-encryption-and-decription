#include <client.h>
int clientSocket, portNum, nBytes;
char file_buffer[3000], path[1024], buffer[3000];
char const key[3000] = "HIDDENKEY";
struct sockaddr_in serverAddr;
socklen_t addr_size;
int i;
void encryption(){
        printf("Specify file name: \n");
        scanf("%s",path);
        FILE* fp;
        fp = fopen(path, "r");
        if (fp == NULL) {
            printf("file does not exist\n");
        }
        fseek(fp, 0, SEEK_END);
        size_t file_size1 = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        if (fread(file_buffer, file_size1, 1, fp) <= 0) {
            printf("unable to copy file into buffer\n");
            exit(1);
        }
        if (sendto(clientSocket, file_buffer, 3000, 0, (struct sockaddr*)&serverAddr,addr_size) < 0) {
            printf("error in sending the file\n");
            exit(1);
        }
        bzero(file_buffer, sizeof(file_buffer));
        nBytes = recvfrom(clientSocket, buffer, 1024, 0, NULL, NULL);
        printf("encrypted file content : \n");
        for (i = 0; i<file_size1; ++i)
            printf("%02X ", buffer[i]);
        printf("\n");
}
void decryption(){
        printf("Specify file name: \n");
        scanf("%s",path);
        FILE* fp;
        fp = fopen(path, "r");
        if (fp == NULL) {
            printf("file does not exist\n");
        }
        fseek(fp, 0, SEEK_END);
        size_t file_size1 = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        if (fread(file_buffer, file_size1, 1, fp) <= 0) {
            printf("unable to copy file into buffer\n");
            exit(1);
        }
        if (sendto(clientSocket, file_buffer, 3000, 0, (struct sockaddr*)&serverAddr,addr_size) < 0) {
            printf("error in sending the file\n");
            exit(1);
        }
        bzero(file_buffer, sizeof(file_buffer));
        nBytes = recvfrom(clientSocket, buffer, 1024, 0, NULL, NULL);

        char x[3000];
        for (i = 0; i < nBytes - 1; ++i)
            x[i] = (char)(buffer[i] ^ key[i]);
         printf("Decrypted file contents \n");
        for (i = 0;i<file_size1 ; ++i)
            printf("%c ", x[i]);
        printf("\n");
}
int main()
{
 
    clientSocket = socket(PF_INET, SOCK_DGRAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5004);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
    addr_size = sizeof serverAddr;
    while (1) {
        int ch=0;
        printf("=======================================\n");
        printf("              menu                    \n");
        printf("=======================================\n");
        printf("1.encryption\n2.decryption\n3.exit\n");
        printf("=======================================\n");
        printf("enter your choice:");
        scanf("%d",&ch);
        switch(ch){
         case 1: encryption();
                 break;
         case 2: decryption();
                 break;
         case 3: exit(1);
         default: printf("invalid options.......");
         }       
        
    }
    return 0;
}
