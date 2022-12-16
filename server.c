#include <sys/types.h>          
#include <sys/socket.h>     
#include <netinet/in.h>     
#include <arpa/inet.h>  
#include <netdb.h>  
#include <unistd.h>     
#include <errno.h>  
#include <stdio.h>  
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#define PORT 11111
#define IP "127.0.0.1"

int main(){
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    // if(sockfd == INVALID_SOCKET){
    //     return 1;
    // }
    
    struct sockaddr_in addr;
    int addrlen = sizeof(addr);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr(IP);
    int bind_server = bind(sockfd,(sockaddr*) &addr,sizeof(addr));

    int listenclient = listen(sockfd,256);
    struct sockaddr_in clients;
    int size_client = sizeof(clients); 
    
    int client = accept(sockfd,(struct sockaddr*) &clients,(socklen_t*)&size_client);
    //int conct = connect(client,(struct sockaddr*) &addr,sizeof(addr));
    
    char buf[1024] = {0};
    int msg = read(client,buf,sizeof(buf));
    std::ofstream file;
	file.open("Client.txt");
	file << buf;
    char msg_to_client[32] = "I`ve got your file!\n";
    // std::cin.getline(msg_to_client,32);
    int send_msg = send(client,msg_to_client,sizeof(msg_to_client),0);
    
    //close(client);
    //printf("Connection closed!\n");
    shutdown(sockfd, SHUT_RDWR);
    return 0;
}
