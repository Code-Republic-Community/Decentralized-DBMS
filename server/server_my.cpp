#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
 
using namespace std;
 
int main()
{
    // Create a socket
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1)
    {
        cerr << "Can't create a socket! Quitting" << endl;
        return -1;
    }
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(55000);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
 
    bind(listening, (sockaddr*)&hint, sizeof(hint));
 
    // Tell Winsock the socket is for listening
    listen(listening, SOMAXCONN);
    
    // Wait for a connection
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    
    int clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
 
    char host[NI_MAXHOST];      // Client's remote name
    char service[NI_MAXSERV];   // Service (i.e. port) the client is connect on
 
    memset(host, 0, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);
 
    if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
    {
        //system("gnome-terminal");
        cout << host << " connected on port " << service << endl;
    }
    else
    {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        cout << host << " connected on port " << ntohs(client.sin_port) << endl;
    }
 
    // Close listening socket
    close(listening);
 
    // While loop: accept and echo message back to client
    char buf[4096];
 
    while (true)
    {
        memset(buf, 0, 4096);
 
        // Wait for client to send data
        int bytesReceived = recv(clientSocket, buf, 4096, 0);
        if (bytesReceived == -1)
        {
            cerr << "Error in recv(). Quitting" << endl;
            break;
        }
 
        if (bytesReceived == 0)
        {
            cout << "Client disconnected " << endl;
            break;
        }
 
        cout << string(buf, 0, bytesReceived) << endl;
 
        // Echo message back to client
        send(clientSocket, buf, bytesReceived + 1, 0);
    }
 
    // Close the socket
    close(clientSocket);
 
    return 0;
}    
    // Bind the ip address and port to a socket
    //«Socaddr_in» կառուցվածքը շատ տարածված է C ծրագրավորման լեզվով socket ծրագրավորման մեջ: 
    //Այս կառուցվածքը թույլ է տալիս կապել վարդակից ցանկալի հասցեով, որպեսզի սերվերը կարողանա լսել հաճախորդների միացման հարցումները:
    //Linux-ի ներքո առավել հաճախ օգտագործվող հասցեների ընտանիքը AF_INET ընտանիքն է: 
    //Սա վարդակին տալիս է IPv4 վարդակից հասցե, որը թույլ է տալիս հաղորդակցվել այլ հոսթների հետ TCP/IP ցանցի միջոցով:
    //sin_port անդամը սահմանում է TCP/IP պորտի համարը վարդակից հասցեի համար: Այս արժեքը պետք է լինի ցանցի բայթերի կարգով:
    //The sin_addr member is defined as the structure in_addr, which holds the IP number in network byte order.
    // If you examine the structure in_addr, you will see that it consists of one 32- bit unsigned integer. 