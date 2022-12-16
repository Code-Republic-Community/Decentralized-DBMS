#include <iostream>
#include <fstream>
#include "../get_ip/get_ipv4.h"
// call function add_IPv4_txt() to create a IP if file exists adds from end . passing the penultimate possible value(s) of host on your local network
// 192.168.x.y    send function x as a string
int main(){
    char ipv4[255][16];
    for (int i = 0 ; i < 255 ;++i){
        ipv4[i][0] = '\0';
    }
    int s;
    std::string num_3;
    while (1){
        printf("\n input number action \n 1 create_ip ");
        printf("\n 2 delete ip_file ");
        printf("\n 3 print ip_number ");
        printf("\n 4 get ip in array");
        printf("\n 5 print ip_array \n");
        std::cin >> s;  
        switch (s){
        case 1:
            std::cout << "3_num" << std::endl;
            std::cin >> num_3; 
            create_IPv4_txt(num_3);
            break;
        case 2:
            std::cout << "3_num" << std::endl;
            std::cin >> num_3;
            delete_IPv4_txt(num_3);
            break;
        case 3:
            print_number();
            break;
        case 4:
            std::cout << "3_num" << std::endl;
            std::cin >> num_3; 
            get_IP(ipv4,num_3);
            break;
        case 5:
            std::cout << sizeof(ipv4)/16;
            for(int i = 0; i < size_ipv4; ++i){
                std::cout << ipv4[i] << std::endl;
            }
            break;
        default:
            break;
        }
    }
}