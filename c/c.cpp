#include <iostream>
#include <winsock2.h>
#include <string>
#include <thread>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define ip_address "127.0.0.1"
#define port 8080
#define bufferSize 1024

void communication_thread(SOCKET client_sock)
{
    std::string message;
    while (true)
    {
        // Receive message from server
        char recv_buf[bufferSize];
        int bytes_received = recv(client_sock, recv_buf, sizeof(recv_buf), 0);
        if (bytes_received == SOCKET_ERROR)
        {
            std::cout << "Error receiving message from server." << std::endl;
            break;
        }
        message = recv_buf;
  
        if (message != "") {
            std::cout << "Message received: " << message << std::endl;
        }
        
        std::cout << "Enter a message to send to the server: ";
        std::cout << std::endl;
    }
}

int main()
{
    WSADATA wsa;
    WORD wVersionRequested;
    wVersionRequested = MAKEWORD(2, 2);
    int error = WSAStartup(wVersionRequested, &wsa);
    if (error != 0) {
        throw std::runtime_error("WSAStartup failed");
    }

    SOCKET client_sock;
    if ((client_sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        std::cout << "failed to create socket." << std::endl;
        exit(EXIT_FAILURE);
    }

    sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(sockaddr_in));
    serv_addr.sin_family = AF_INET;
    inet_pton(AF_INET, ip_address, &serv_addr.sin_addr);
    serv_addr.sin_port = htons(port);
    
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    std::string colour;
    std::cout << "What colour do you want to write in: ";
    std::cin >> colour;

    if (colour == "blue") {
        SetConsoleTextAttribute(console, FOREGROUND_BLUE);
    }
    else if (colour == "sapphire") {
        SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_GREEN);
    }
    else if (colour == "green") {
        SetConsoleTextAttribute(console, FOREGROUND_GREEN);
    }
    else if (colour == "red") {
        SetConsoleTextAttribute(console, FOREGROUND_RED);
    }
    else if (colour == "white") {
        SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    }
    else if (colour == "purple") {
        SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_RED);
    }
    else if (colour == "yellow") {
        SetConsoleTextAttribute(console, FOREGROUND_GREEN | FOREGROUND_RED);
    }
    system("cls");

    if (connect(client_sock, (sockaddr*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR) 
    {
        std::cout << "Failed to connect to peer. " << WSAGetLastError() << std::endl;
        closesocket(client_sock);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    // Start a thread to handle communication with the server
    std::thread t(communication_thread, client_sock);

    std::string message;
    while (true)
    {
        std::getline(std::cin, message);

        if (message == "exit") {
            break;
        }
        else if (message == "clear") {
            system("cls");//Clear the console
            continue;
        }
        else if (message == "restore default colour") {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            continue;
        }
        send(client_sock, message.c_str(), message.size() + 1, 0);
    }

    // Wait for the communication thread to finish
    t.join();

    // Close the socket and cleanup
    closesocket(client_sock);
    WSACleanup();
}
