// #ifndef ConnectionFunctions
// #define ConnectionFunctions

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
#include <cstring>
#include <sstream>
#include <fstream>
#include <pthread.h>

#define PORT1 11111
#define PORT2 22222
// #define IP "127.0.0.1"

void* ConnectAsClient(void* sockfd,const std::string& filepath,std::string IP){
    struct sockaddr_in addr;
    int addrlen = sizeof(addr);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr((const char*) &IP);
    addr.sin_port = htons(PORT2);
    int cnn = connect(*(int*)sockfd,(struct sockaddr*) &addr,sizeof(addr));
    char buf[16384] = {0};
    std::stringstream ss;
    std::ifstream file;
    file.open(filepath); 
    ss << file.rdbuf();
    strcpy(buf,ss.str().c_str());
    send(*(int*)sockfd,buf,sizeof(buf),0);
    // char rcv[256] = {0};
    // recv(*(int*)sockfd,rcv,256,0);
    // printf("Server: %s\n",rcv);
    return sockfd;
}

void* ConnectAsServer(void* sockfd){
    struct sockaddr_in addr;
    int addrlen = sizeof(addr);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT2);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    int bind_server = bind(*(int*)sockfd,(sockaddr*) &addr,sizeof(addr));
    if(bind_server == -1) {
        std::cerr << "Unable to bind socket!\nExiting programm...\n";
        return NULL;
    }
    int listenclient = listen(*(int*)sockfd,256);
    if(listenclient == -1) {
        std::cerr << "Unable to listen for connections!\nExiting programm...\n";
        return NULL;
    }
    struct sockaddr_in clients;
    int size_client = sizeof(clients); 
    while(true){
        int client = accept(*(int*)sockfd,(struct sockaddr*) &clients,(socklen_t*)&size_client);
        char buf[16384] = {0};
        int msg = read(client,buf,sizeof(buf));
        std::ofstream file;
	    file.open("Client1.txt");
	    file << buf;
        //char msg_to_client[32] = "I`ve got your file!\n";
        //int send_msg = send(client,msg_to_client,sizeof(msg_to_client),0);
    }
    return sockfd;
}