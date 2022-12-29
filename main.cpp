#include "ConnectionFunctions.h"
#include <pthread.h>
#include <vector>


int main(){
    int server_socket = socket(AF_INET,SOCK_STREAM,0);
    if(server_socket == -1){
        std::cerr << "Unable to connect!\nRestart program!\nExiting programm...\n";
        return 1;
    }
    std::vector<std::string> ips = {"127.0.0.1"};
    pthread_t running_server;
    pthread_create(&running_server,NULL,ConnectAsServer,(void*)&server_socket);
    std::cout << "Welcome to DBMS.\nEnter operation You want to perform.\n";
    while(true){
        std::cout << "[1] Open file\n[2] Upload file\n";
        char op;
        std::cin >> op;
        switch(op){
        case '1':
            //To Do
            std::cout << "Done!\n";
            break;
        case '2':
            std::cout << "Enter file path:\t-";//.\t(hint: enter \'\\\' symbols as \\\\\n)";
            std::string filepath;
            std::cin >> filepath;
            for(int i = 0; i < ips.size(); ++i){
                int client_socket = socket(AF_INET,SOCK_STREAM,0);
                if(client_socket == -1){
                    std::cerr << "Unable to connect to network!\nRestart!\nExiting programm...\n";
                    return 1;
                }
                ConnectAsClient((void*)&client_socket,filepath,ips[i]);
                close(client_socket);
            }
            std::cout << "Done!\n";
            break;
        // default:
        //     std::cout << "Invalid operation!\n";
        //     break; 
        }
    }
    pthread_join(running_server,NULL);
    return 0;
}