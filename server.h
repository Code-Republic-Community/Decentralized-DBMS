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

class Server{
public:
    Server();
    const char* GetIp() const;
    int GetPort() const;
    int GetSocket() const;
    sockaddr_in* GetServerAddress() const;
    void* ConnectAsServer(void* Client);
    ~Server() = default;
private:
    const char* m_IP;
    int m_PORT;
    int m_SOCK;
    sockaddr_in m_server_addr;
};

Server::Server() {
    // m_IP = ...
    m_PORT = 15365;
    m_SOCK = socket(AF_INET,SOCK_STREAM,0);
    m_server_addr.sin_family = AF_INET;
    m_server_addr.sin_port = htnos(m_PORT);
    m_server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
} 

int Server::GetIp() const {
    return this->m_IP;
}

int Server::GetPort() const {
    return this->m_PORT;
}

int Server::GetSocket() const {
    return this->m_sockfd;
}

sockaddr_in* Server::GetServerAddress() const {
    return &this->m_server_addr;
}

void* Server::ConnectAsServer(void* serv){
    Server* server = (Server*)serv;
    int addrlen = sizeof(server->GetServerAddress());
    if(server->GetSocket() == -1){
        std::cerr << "Unable to create socket!\nExiting programm...\n";
        return NULL;
    }
    int bind_server = bind(server->GetSocket(),(sockaddr*) server->GetServerAddress(),addrlen);
    if(bind_server == -1){
        std::cerr << "Unable to bind socket!\nExiting programm...\n";
        return NULL;
    }
    int listenclient = listen(server->GetSocket(),512);
    if(listenclient == -1){
        std::cerr << "Unable to listen for connections!\nExiting programm...\n";
    }
    sockaddr_in clients;
    int size_client = sizeof(clients); 
    while(true){
        int client = accept(server->GetSocket(),(struct sockaddr*) &clients,(socklen_t*)&size_client);
        char buf[16384] = {0};
        int msg = read(client,buf,sizeof(buf));
        std::ofstream file;
	    file.open("Anun.txt");
	    file << buf;
        char msg_to_client[32] = "Success";
        int send_msg = send(client,msg_to_client,sizeof(msg_to_client),0);
    }
    return NULL;
}