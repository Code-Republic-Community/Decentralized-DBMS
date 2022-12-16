#include <iostream>
#include <fstream>
#include "../get_ip/get_ipv4.h"
// call function add_IPv4_txt() to create a IP if file exists adds from end . passing the penultimate possible value(s) of host on your local network
// 192.168.x.y    send function x as a string
int main(){
    my_IPv4 Ip;
    int s;
    std::string num_3;
    while (1){
        printf("\n input number action \n 1 create_ip ");
        printf("\n 2 delete ip_file ");
        printf("\n 3 get ip_number ");
        printf("\n 4 get ip in array");
        printf("\n 5 print ip_array \n");
        std::cin >> s;  
        switch (s > 1){
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
            break;
        case 5:
            for(int i = 0; i < Ip.count_ipv4; ++i){
                std::cout << Ip.ipv4[i] << std::endl;
            }
            break;
        }
    }
}