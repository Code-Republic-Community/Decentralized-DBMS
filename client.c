#include <sys/types.h>          
#include <sys/socket.h>     
#include <netinet/in.h>     
#include <arpa/inet.h>  
#include <netdb.h>  
#include <unistd.h>     
#include <errno.h>  
#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>

#define PORT 11111
#define IP "127.0.0.1"

int main(){
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    
    struct sockaddr_in addr;
    int addrlen = sizeof(addr);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(IP);
    addr.sin_port = htons(PORT);
    int cnn = connect(sockfd,(struct sockaddr*) &addr,sizeof(addr));
    while(true){
        char buf[1024] = {0};
        std::stringstream ss;
        std::ifstream file;
        file.open("myfile.txt"); 
        ss << file.rdbuf();
        strcpy(buf,ss.str().c_str());
        char rcv[256] = {0};
        //std::cin.getline(buf,256);
        send(sockfd,buf,256,0);
        recv(sockfd,rcv,256,0);
        printf("Alice: %s\n",rcv);
    }
    
    return 0;
}
