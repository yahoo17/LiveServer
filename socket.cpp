#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define MESSAGE_LEN 1024
#define PORT 8111
int main(int argc,char * argv[])
{
    int sock_fd=socket(PF_INET,SOCK_STREAM,0);
    if(sock_fd==-1){
        std::cout<<"Fail to create socket!\n";
        exit(-1);
    }
    int on = 1;
    int ret = setsockopt(sock_fd,
                SOL_SOCKET,
                SO_REUSEADDR,
                on,
                sizeof(on));
    if(ret==-1){
        std::cout<<"Fail to set socket option\n";
    }

    struct sockaddr_in localaddr;
    localaddr.sin_family = AF_INET;
    localaddr.sin_port = PORT;
    localaddr.sin_addr.s_addr = INADDR_ANY; //任何一个ip地址都监听
    bzero(&localaddr.sin_zero,8);
    ret = bind(sock_fd,(struct sockaddr * )&localaddr,sizeof(struct sockaddr));

    if(ret==-1){
        std::cout<<"Fail to bind Address\n";
        exit(-1);
    }

    //缓冲的长度 ,毫秒级的并发10个
    int backlog = 10;
    ret = listen(sock_fd,backlog);
    if(ret==-1){
        std::cout<<"Fail to Listen \n";
        exit(-1);
    }
    
    struct sockaddr_in remoteaddr;
    char in_buff [MESSAGE_LEN]={0,};
    int accept_fd;
    for(;;){
        socklen_t addr_len=sizeof(struct sockaddr);
        accept_fd = accept(sock_fd,
                          (struct sockaddr * )& remoteaddr,
                            &addr_len);
        //一般没问题

        for(;;){
            ret = recv(accept_fd,(void *)in_buff,MESSAGE_LEN,0);
            //实际长度ret

            if(ret == 0){
                break;
            }

            std::cout<<"recv:"<<in_buff<<"\n";
            send(accept_fd,(void*) in_buff,MESSAGE_LEN,0);
        }

        close(accept_fd);

    }

    close(sock_fd);//关闭监听的socket

    return 0;


}