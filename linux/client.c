#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <linux/in.h>
#include <string.h>

#define SERVER_IP   "192.168.1.101"
#define PORT_NUM    8888
#define BUFFER_LEN  1024

int main()
{
    int cfd;
    int recBytes;
    int sin_size;
    char buffer[BUFFER_LEN] = {0};
    struct sockaddr_in s_add, c_add;

    cfd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == cfd){
        printf("socket fail !\n");
        return -1;
    }

    bzero(&s_add, sizeof(struct sockaddr_in));
    s_add.sin_family = AF_INET;
    s_add.sin_addr.s_addr = inet_addr(SERVER_IP);
    s_add.sin_port = htons(PORT_NUM);

    if(-1 == connect(cfd, (struct sockaddr *)(&s_add), sizeof(struct sockaddr))){
        printf("connect fail!\n");
        return -1;
    }
    printf("connect ok\n");
    
    recBytes = read(cfd, buffer, BUFFER_LEN);
    if(-1 == recBytes){
        printf("read data fail!\n");
        return -1;
    }

    buffer[recBytes]='\0';
    printf("read: %s\n", buffer);
    
    // getchar();  //if not close socket fd, the server would not finish recv 
    close(cfd);
    return 0;
}
