#include <iostream>
#include <unistd.h>
#include <stdlib.h>

int main(int argc , char *argv[])
{
   if(daemon(0,0)<0){
       //0 nochangedir
       //0 noclose std in std out std err

       std::cout<<"error"<<std::endl;
       exit(-1);
   }

   while(1){

       sleep(1);
   }
}