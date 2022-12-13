#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
 
using namespace std;
//o_server@ tvyal poxancox servern e 
int main()
{
    int sock_fd, new_sock_fd, portno;
    socklen_t o_server_length;
    struct sockaddr_in my_serv_addr, o_server__addr;
    char bufer[100];
    sock_fd =  socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd == -1){
        std::cout << "socked not defined";
        return -1;
    }
    bzero((char *) &my_serv_addr, sizeof(my_serv_addr));
    return 0;
}
//14  veradarcnum e -1 sxali depqum //AF_INET cuyc e talis vor stexcvel e IPV4 internet protocol, ardzanagrutyan tesak@ tcp/ip e (SOCK_STREAM),
//himnakanum 3rd argument@ havasarecnum enq 0_i

    // Bind the ip address and port to a socket
    //«Socaddr_in» կառուցվածքը շատ տարածված է C ծրագրավորման լեզվով socket ծրագրավորման մեջ: 
    //Այս կառուցվածքը թույլ է տալիս կապել վարդակից ցանկալի հասցեով, որպեսզի սերվերը կարողանա լսել հաճախորդների միացման հարցումները:
    //Linux-ի ներքո առավել հաճախ օգտագործվող հասցեների ընտանիքը AF_INET ընտանիքն է: 
    //Սա վարդակին տալիս է IPv4 վարդակից հասցե, որը թույլ է տալիս հաղորդակցվել այլ հոսթների հետ TCP/IP ցանցի միջոցով:
    //sin_port անդամը սահմանում է TCP/IP պորտի համարը վարդակից հասցեի համար: Այս արժեքը պետք է լինի ցանցի բայթերի կարգով:
    //The sin_addr member is defined as the structure in_addr, which holds the IP number in network byte order.
    // If you examine the structure in_addr, you will see that it consists of one 32- bit unsigned integer.  