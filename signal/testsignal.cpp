#include <signal.h>
#include <iostream>

#include <unistd.h>

void sighandle(int sig){
    std::cout<<"received signal"<<sig<<std::endl;

}

int main (int argc, char * argv[])
{
    signal(SIGINT,sighandle);
    signal(SIGQUIT,sighandle);
    signal(SIGHUP,sighandle);
    pause();
    return 0;
}