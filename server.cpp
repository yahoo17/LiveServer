/* Server class
* @author yanhao
* @date 2020/9/22
* @copyleft GPL 2.0
*/
#include "server.h"
#include <iostream>
#include <unistd.h>
namespace advance {

Server::Server(){
    std::cout << "Server construct"<<std::endl;
}

Server::~Server(){
    std::cout<<" destruct...\n";
}

void Server::run(){

    while(1){
        std::cout<<"runing..."<<std::endl;
        ::usleep(1000000);

    }
}
}