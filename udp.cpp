//udp.cpp
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/sockets>
#include <stdlib.h>
#include <arpa/in.h>
#include <signal.h>

class Server
{
public:

    Server();
    ~Server();
public:
    void run();
    void init();
private:
    const int MAX_LENGTH = 1024;
    char recvbuff[MAX_LENGTH];
}
void Server::init(){
    int listen_fd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in serveraddr;
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_addr.s_addr=INADDR_ANY;
    serveraddr.sin_port=8881;

    bind(listen_fd,(struct sockaddr*)&sockaddr_in,sizeof(struct sockaddr));

    listen(listen_fd,10);

    struct sockaddr_in remoteaddr;
    while(1){
        int sock_fd = accept();
        socklen_t addr_len=sizeof(struct sockaddr);
        int ret = recv(recvbuff,(struct sockaddr*)&remoteaddr,&addr_len);
        recvbuff[ret]='\0';
        std::cout<<"recv:"<<recvbuff<<std::endl;
        if(ret<=0){
            break;
        }
        send(recvbuff,(void *)recvbuff,MAX_LENGTH,0);
        close(sock_fd);
        
    }
    close(listen_fd);
    
}

void Server::run(){
    init();

}
void runServer(){
    Server * sever= new Server();
    sever->run();
}
void sighandler(int sig){

}
int main(int argc ,char * argv[])
{
    
    int pid;
    if((pid=fork())!=0){
        std::cout<<"parent exit";
        exit(1);
    }else{
        setsid();
        
        if(chdir("/")<0){
            //error
        }
        int fd = open("/dev/null");
        dup2(fd,STDOUT_FILENO);
        dup2(fd,STDIN_FILENO);
        dup2(fd,STDERR_FILENO);
        signal(SIGINT,sighandler);
        signal(SIGQUIT,sighandler);
        runServer();
        
    }


}