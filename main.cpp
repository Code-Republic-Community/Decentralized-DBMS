#include "BlockChain.h"
//#include "boost/property_tree/json_parser.hpp"
#include <pthread.h>
//#include <vector>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
//#include <fstream>
#include <string>
//#include <pthread.h>
#include <iostream>
#include "get_ipv4.h"

#define TRUE 1
#define FALSE 0
#define PORT 8888

void* run_server(void* nothing)
{
    int opt = TRUE;
    int master_socket , addrlen , new_socket , client_socket[30] ,
            max_clients = 30 , activity, i , valread , sd;
    int max_sd;
    struct sockaddr_in address;

    char buffer[16000];

    //set of socket descriptors
    fd_set readfds;

    //a message
    char *message = "ECHO Daemon v1.0 \r\n";

    //initialise all client_socket[] to 0 so not checked
    for (i = 0; i < max_clients; i++)
    {
        client_socket[i] = 0;
    }

    //create a master socket
    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    //set master socket to allow multiple connections ,
    //this is just a good habit, it will work without this
    if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
                   sizeof(opt)) < 0 )
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    //type of socket created
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    //bind the socket to localhost port 8888
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Listener on port %d \n", PORT);

    //try to specify maximum of 3 pending connections for the master socket
    if (listen(master_socket, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    //accept the incoming connection
    addrlen = sizeof(address);
    puts("Waiting for connections ...");

    while(TRUE)
    {
        //clear the socket set
        FD_ZERO(&readfds);

        //add master socket to set
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;

        //add child sockets to set
        for ( i = 0 ; i < max_clients ; i++)
        {
            //socket descriptor
            sd = client_socket[i];

            //if valid socket descriptor then add to read list
            if(sd > 0)
                FD_SET( sd , &readfds);

            //highest file descriptor number, need it for the select function
            if(sd > max_sd)
                max_sd = sd;
        }

        //wait for an activity on one of the sockets , timeout is NULL ,
        //so wait indefinitely
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);

        if ((activity < 0) && (errno!=EINTR))
        {
            printf("select error");
        }

        //If something happened on the master socket ,
        //then its an incoming connection
        if (FD_ISSET(master_socket, &readfds))
        {
            if ((new_socket = accept(master_socket,
                                     (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            //inform user of socket number - used in send and receive commands
            printf("New connection , socket fd is %d , ip is : %s , port : %d\n" , new_socket , inet_ntoa(address.sin_addr) , ntohs
                    (address.sin_port));

            //send new connection greeting message
            if( send(new_socket, message, strlen(message), 0) != strlen(message) )
            {
                perror("send");
            }

            puts("Welcome message sent successfully");

            //add new socket to array of sockets
            for (i = 0; i < max_clients; i++)
            {
                //if position is empty
                if( client_socket[i] == 0 )
                {
                    client_socket[i] = new_socket;
                    printf("Adding to list of sockets as %d\n" , i);

                    break;
                }
            }
        }

        //else its some IO operation on some other socket
        for (i = 0; i < max_clients; i++)
        {
            sd = client_socket[i];
            if (FD_ISSET( sd , &readfds))
            {
                //Check if it was for closing , and also read the
                //incoming message
                if ((valread = read( sd , buffer, 1024)) == 0)
                {
                    //Somebody disconnected , get his details and print
                    getpeername(sd , (struct sockaddr*)&address , \
						(socklen_t*)&addrlen);
                    printf("Host disconnected , ip %s , port %d \n" ,
                           inet_ntoa(address.sin_addr) , ntohs(address.sin_port));

                    //Close the socket and mark as 0 in list for reuse
                    close( sd );
                    client_socket[i] = 0;
                }
                    //Echo back the message that came in
                else
                {
                    //set the string terminating NULL byte on the end
                    //of the data read
                    buffer[valread] = '\0';
                    char* ptr = buffer;
                    std::ofstream file;
                    std::string filename;
                    int i = 0;
                    while(buffer[i] != ' '){
                        filename += buffer[i];
                        ++i;
                    }
                    //ptr += i;
                    file.open(filename.c_str());
                    file << ptr;
                    puts(buffer);
                    //send(sd , buffer , strlen(buffer) , 0 );
                }
            }
        }
    }

    return NULL;
}



int main() {
    BlockChain chain;   //created chain with genesis bloack
    std::cout << "============================================================" << std::endl;
    std::cout << "index: " << chain.get_last_block().get_index() << std::endl;
    std::cout << "hash:  " << chain.get_last_block().get_hash() << std::endl;
    std::cout << "previous hash: " << chain.get_last_block().get_prev_hash() << std::endl;
    std::cout << "count: " << chain.count_of_blocks() << std::endl;
    std::cout << "============================================================" << std::endl;
    //Create second block
    Data d1;
    d1.text = "Rafo";
    chain.add_block(d1);
    std::cout << "index: " << chain.get_last_block().get_index() << std::endl;
    std::cout << "hash:  " << chain.get_last_block().get_hash() << std::endl;
    std::cout << "previous hash: " << chain.get_last_block().get_prev_hash() << std::endl;
    std::cout << "count: " << chain.count_of_blocks() << std::endl;
    std::cout << "============================================================" << std::endl;
    //Create third block
    Data d2;
    d2.text = "Vahe";
    chain.add_block(d2);
    std::cout << "index: " << chain.get_last_block().get_index() << std::endl;
    std::cout << "hash:  " << chain.get_last_block().get_hash() << std::endl;
    std::cout << "previous hash: " << chain.get_last_block().get_prev_hash() << std::endl;
    std::cout << "count: " << chain.count_of_blocks() << std::endl;
    std::cout << "============================================================" << std::endl;
    Data d3;
    d3.text = "abcdefg ABCDEFG";
    chain.add_block(d3);
    std::cout << "index: " << chain.get_last_block().get_index() << std::endl;
    std::cout << "hash:  " << chain.get_last_block().get_hash() << std::endl;
    std::cout << "previous hash: " << chain.get_last_block().get_prev_hash() << std::endl;
    std::cout << "count: " << chain.count_of_blocks() << std::endl;
    std::cout << "============================================================" << std::endl;
    //chain.print_chain_blocks();
    chain.convert_chain_to_json();

    my_IPv4 Ip;
    int s;
    std::string num_3;
    int k = 0;
    while (k != 4){
        printf("\n input number action \n 1 create_ip ");
        printf("\n 2 delete ip_file ");
        printf("\n 3 get ip_number ");
        printf("\n 4 get ip in array");
        printf("\n 5 print ip_array \n");
        std::cin >> s;
        switch (s){
            case 1:
                std::cout << "3_num" << std::endl;
                std::cin >> num_3;
                Ip.create_IPv4_txt(num_3);
                break;
            case 2:
                std::cout << "3_num" << std::endl;
                std::cin >> num_3;
                Ip.delete_IPv4_txt(num_3);
                break;
            case 4:
                std::cout << "3_num" << std::endl;
                std::cin >> num_3;
                Ip.get_IP(num_3);
            case 5:
                for(int i = 0; i < Ip.count_ipv4; ++i){
                    std::cout << Ip.ipv4[i] << std::endl;
                }
                break;
        }
       k++;
    }

    pthread_t server;
    pthread_create(&server,NULL,run_server,NULL);
    //std::string filename = "../hello.txt";
    //char sending_message[] = "netcat localhost 8888 < ";
    //system(strcat(sending_message,filename.c_str()));
    std::string filename = "file.json";

    for(int i = 0; i<Ip.count_ipv4; ++i){
        std::string cc = "netcat ";
        cc += Ip.ipv4[i];
        cc += " 8888 < ";
        cc += filename;
        system(cc.c_str());
    }
    pthread_join(server,NULL);

/*
    my_IPv4 Ip;
    std::string num_3 = "10";
    Ip.create_IPv4_txt(num_3);
    Ip.get_IP(num_3);

    //std::string ipp[] = {"192.168.11.98", "192.168.10.25"};
    pthread_t server;
    pthread_create(&server,NULL,run_server,NULL);
    //std::string filename = "../hello.txt";
    //char sending_message[] = "netcat localhost 8888 < ";
    //system(strcat(sending_message,filename.c_str()));
    std::string filename = "file.json";

    for(int i = 0; i<Ip.count_ipv4; ++i){
        std::string cc = "netcat ";
        cc += Ip.ipv4[i];
        cc += " 8888 < ";
        cc += filename;
        system(cc.c_str());
    }
    pthread_join(server,NULL);
*/
/*
    pthread_t server;
    pthread_create(&server,NULL,run_server,NULL);
    //std::string filename = "../hello.txt";
    //char sending_message[] = "netcat localhost 8888 < ";
    //system(strcat(sending_message,filename.c_str()));
    system("netcat 192.168.11.98 8888 < file.json");
    system("netcat 192.168.10.25 8888 < file.json");
    pthread_join(server,NULL);
*/
    return 0;
}
