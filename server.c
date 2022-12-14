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
    while(true){
        struct sockaddr_in clients;
        int size_client = sizeof(clients); 
    
        int client = accept(sockfd,(struct sockaddr*) &clients,(socklen_t*)&size_client);
        //int conct = connect(client,(struct sockaddr*) &addr,sizeof(addr));
    
    
        char buf[1024];
        int msg = read(client,buf,sizeof(buf));
        std::cout << "Bob: "<< buf << std::endl;
        char msg_to_client[32];
        std::cin.getline(msg_to_client,32);
    
        int send_msg = send(client,msg_to_client,sizeof(msg_to_client),0);
    }
    //close(client);
    
    //printf("Connection closed!\n");
    shutdown(sockfd, SHUT_RDWR);
    /*
    // fd_set master;
	// FD_ZERO(&master);

	// // Add our first socket that we're interested in interacting with; the listening socket!
	// // It's important that this socket is added for our server or else we won't 'hear' incoming
	// // connections 
	// FD_SET(listenclient, &master);

	// // this will be changed by the \quit command (see below, bonus not in video!)
	// bool running = true; 

	// while (running)
	// {
	// 	// Make a copy of the master file descriptor set, this is SUPER important because
	// 	// the call to select() is _DESTRUCTIVE_. The copy only contains the sockets that
	// 	// are accepting inbound connection requests OR messages. 

	// 	// E.g. You have a server and it's master file descriptor set contains 5 items;
	// 	// the listening socket and four clients. When you pass this set into select(), 
	// 	// only the sockets that are interacting with the server are returned. Let's say
	// 	// only one client is sending a message at that time. The contents of 'copy' will
	// 	// be one socket. You will have LOST all the other sockets.

	// 	// SO MAKE A COPY OF THE MASTER LIST TO PASS INTO select() !!!

	// 	fd_set copy = master;

	// 	// See who's talking to us
	// 	int socketCount = select(0, &copy, 0, 0, 0);

	// 	// Loop through all the current connections / potential connect
	// 	for (int i = 0; i < socketCount; i++)
	// 	{
	// 		// Makes things easy for us doing this assignment
	// 		int sock = copy.fds_bits[i];
	// 		// Is it an inbound communication?
	// 		if (sock == listenclient)
	// 		{
	// 			// Accept a new connection
	// 			int client = accept(listenclient, 0, 0);

	// 			// Add the new connection to the list of connected clients
	// 			FD_SET(client, &master);

	// 			// Send a welcome message to the connected client
	// 			std::string welcomeMsg = "Welcome to the Awesome Chat Server!\r\n";
	// 			send(client, welcomeMsg.c_str(), welcomeMsg.size() + 1, 0);
	// 		}
	// 		else // It's an inbound message
	// 		{
	// 			char buf[4096] = {0};
	// 			//ZeroMemory(buf, 4096);
				
	// 			// Receive message
	// 			int bytesIn = recv(sock, buf, 4096, 0);
	// 			if (bytesIn <= 0)
	// 			{
	// 				// Drop the client
	// 				close(sock);
	// 				FD_CLR(sock, &master);
	// 			}
	// 			else
	// 			{
	// 				// Check to see if it's a command. \quit kills the server
	// 				if (buf[0] == '\\')
	// 				{
	// 					// Is the command quit? 
	// 					std::string cmd = std::string(buf, bytesIn);
	// 					if (cmd == "\\quit")
	// 					{
	// 						running = false;
	// 						break;
	// 					}

	// 					// Unknown command
	// 					continue;
	// 				}

	// 				// Send message to other clients, and definiately NOT the listening socket

	// 				for (int i = 0; i < *master.fds_bits; i++)
	// 				{
	// 					int outSock = master.fds_bits[i];
	// 					if (outSock != listenclient && outSock != sock)
	// 					{
	// 						std::ostringstream ss;
	// 						ss << "SOCKET #" << sock << ": " << buf << "\r\n";
	// 						std::string strOut = ss.str();

	// 						send(outSock, strOut.c_str(), strOut.size() + 1, 0);
	// 					}
	// 				}
	// 			}
	// 		}
	// 	}
	// }

	// // Remove the listening socket from the master file descriptor set and close it
	// // to prevent anyone else trying to connect.
	// FD_CLR(listenclient, &master);
	// close(listenclient);
	
	// // Message to let users know what's happening.
	// std::string msg = "Server is shutting down. Goodbye\r\n";

	// while (sizeof(master) > 0)
	// {
	// 	// Get the socket number
	// 	int sock = master.fds_bits[0];

	// 	// Send the goodbye message
	// 	send(sock, msg.c_str(), msg.size() + 1, 0);

	// 	// Remove it from the master file list and close the socket
	// 	FD_CLR(sock, &master);
	// 	close(sock);
	// }
    */
    return 0;
}

