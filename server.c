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
#define IP "127.0.0.1"

void* ConnectAsClient(void* sockfd){
    struct sockaddr_in addr;
    int addrlen = sizeof(addr);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(IP);
    addr.sin_port = htons(PORT2);
    // while(cnn != 0){
    int cnn = connect(*(int*)sockfd,(struct sockaddr*) &addr,sizeof(addr));
    // }
    char buf[1024] = {0};
    std::stringstream ss;
    std::ifstream file;
    file.open("myfile2.txt"); 
    ss << file.rdbuf();
    strcpy(buf,ss.str().c_str());
    char rcv[256] = {0};
    send(*(int*)sockfd,buf,256,0);
    recv(*(int*)sockfd,rcv,256,0);
    printf("Server: %s\n",rcv);
    return sockfd;
}

void* ConnectAsServer(void* sockfd){
    struct sockaddr_in addr;
    int addrlen = sizeof(addr);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT1);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    int bind_server = bind(*(int*)sockfd,(sockaddr*) &addr,sizeof(addr));

    int listenclient = listen(*(int*)sockfd,256);
    struct sockaddr_in clients;
    int size_client = sizeof(clients); 
    
    int client = accept(*(int*)sockfd,(struct sockaddr*) &clients,(socklen_t*)&size_client);
    char buf[1024] = {0};
    int msg = read(client,buf,sizeof(buf));
    std::ofstream file;
	file.open("Client1.txt");
	file << buf;
    char msg_to_client[32] = "I`ve got your file!\n";
    int send_msg = send(client,msg_to_client,sizeof(msg_to_client),0);
    return sockfd;
}


int main(){
    int sock_for_server = socket(AF_INET,SOCK_DGRAM,0);
    int sock_for_client = socket(AF_INET,SOCK_STREAM,0);
    // pthread_t thread;
    ConnectAsServer(&sock_for_server);
    // pthread_create(&thread,NULL,ConnectAsClient,(void*)&sock_for_client);
    // ConnectAsClient((void*)&sock_for_client);
    // pthread_join(thread,NULL);
    shutdown(sock_for_server, SHUT_RDWR);
    shutdown(sock_for_client, SHUT_RDWR);
    return 0;
}