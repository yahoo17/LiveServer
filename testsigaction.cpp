//testsigaction.cpp
#include <iostream>
#include <signal.h>
#include <unistd.h>

void sighandler(int sig)
{
    std::cout<<"signal is :"<<sig<<"\n";
}

int main(int argc , char * argv[])
{
    struct sigaction act,oact;

    act.sa_handler = sighandler;
    sigfillset(&act.sa_mask);
    act.sa_flags=0;
    
    sigaction(SIGINT,&act,&oact);
    pause();
    return 0;
}