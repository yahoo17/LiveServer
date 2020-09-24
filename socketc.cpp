//socketc.cpp
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#define MESSAGE_LEN 1024
#define PORT 8111
int main(int argc, char * argv[])
{
    
    int socket_fd = socket(AF_INET,SOCK_STREAM,0);
    if(socket_fd<0){
        std::cout<<"Create socket failed\n";
        exit(-1);
    }

    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = PORT;
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    //inet 将字符串转地址


    int ret = connect(socket_fd,
                        (struct sockaddr *)&serveraddr,
                         sizeof(struct sockaddr));

    if(ret < 0){
        std::cout<<"Connect socket failed\n";
        exit(-1);
    }

    char sendbuf[MESSAGE_LEN]={0,};
    char recvbuf[MESSAGE_LEN]={0,};
    while(1){
        memset(sendbuf,0,sizeof sendbuf);
        gets(sendbuf);
        ret = send(socket_fd,sendbuf,strlen(sendbuf),0);

        if(ret<= 0){
            std::cout<<"send error socket failed\n Maybe server close the connection\n";
            break;
        }
        
        if(strcmp(sendbuf,"quit")== 0){
            break;
        }
        ret = recv(socket_fd,recvbuf,MESSAGE_LEN,0);
        recvbuf[ret]='\0';
        std::cout<<"recv:"<<recvbuf<<std::endl;
        
    }

    close(socket_fd);
}