#include <iostream>
#include <thread>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define ip_address "127.0.0.1"
#define port 8080
#define bufferSize 1024

SOCKET other_client_sock;
SOCKET client_sock1;

void communication_thread(SOCKET client_sock)
{
    std::string message;
    while (true)
    {
        // Receive message from client
        char recv_buf[bufferSize];
        int bytes_received = recv(client_sock, recv_buf, sizeof(recv_buf), 0);
        if (bytes_received == SOCKET_ERROR)
        {
            std::cout << "Error receiving message from client." << std::endl;
            break;
        }
        message = recv_buf;

        if (client_sock == other_client_sock) {
            send(client_sock1, message.c_str(), message.size() + 1, 0);
        }
        else {
            send(other_client_sock, message.c_str(), message.size() + 1, 0);
        }
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

    SOCKET server_sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    bind(server_sock, (sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(server_sock, SOMAXCONN);

    sockaddr_in client_addr;
    int client_size = sizeof(client_addr);
    client_sock1 = accept(server_sock, (sockaddr*)&client_addr, &client_size);
    other_client_sock = accept(server_sock, (sockaddr*)&client_addr, &client_size);

    // Start the communication threads
    std::thread thread1(communication_thread, client_sock1);
    std::thread thread2(communication_thread, other_client_sock);

    thread1.join();
    thread2.join();

    // Close the sockets and clean up the Winsock library
    closesocket(client_sock1);
    closesocket(other_client_sock);
    closesocket(server_sock);
    WSACleanup();
}

