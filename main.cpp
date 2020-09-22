#include <iostream>
#include "server.h"
int main(int argc ,char * argv[])
{
    advance::Server * server =new advance::Server();
    if(server){
        server->run();
    }

    return 0;
}