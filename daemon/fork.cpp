#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
using namespace std;
//
void daemonize(){
    
    pid_t pid;
    //子进程是0
    if((pid= fork())<0){
        cout<<" can't create subprocess!\n";
    }else{
        if(pid !=0){
            //父进程
            exit(0);
        }
    }

    setsid();
    if(chdir("/")<0){
        cout<<"can't change dir!\n";
        exit(-1);
    }
    int fd;
    fd = open("/dev/null",O_RDWR);
    dup2(fd,STDIN_FILENO);
    dup2(fd,STDOUT_FILENO);
    dup2(fd,STDERR_FILENO);

    return ;
}
int main()
{
    daemonize();

    while(1){
        sleep(1);
    }
}