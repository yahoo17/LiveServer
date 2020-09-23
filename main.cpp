/* Server class
** @author yanhao
* @date 2020/9/22
* @copyleft GPL 2.0
*/
#include <iostream>
#include "server.cpp"
int main(int argc ,char * argv[])
{
    advance::Server * server =new advance::Server();
    if(server){
        server->run();
    }

    return 0;
}