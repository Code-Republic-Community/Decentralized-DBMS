#include <iostream>
#include <fstream>
//#include "../get_ip/get_ipv4.h"
// call function add_IPv4_txt() to create a IP if file exists adds from end . passing the penultimate possible value(s) of host on your local network
// 192.168.x.y    send function x as a string
int main(){
    /*int s;
    char **ip;
    std::string num_3;
    while (1){
        std::cout << "case" <<std::endl;
        std::cin >> s;
        std::cout << "3_num" << std::endl;
        std::cin >> num_3;   
        switch (s){
        case 1:
            add_IPv4_txt(num_3);
            break;
        case 2:
            delete_IPv4_txt(num_3);
            break;
        case 3:
            print_number();
            break;
        case 4:
            get_IP(ip,num_3);
            break;
        case 5:
            for(int i = 0; i < 50; ++i)
                std::cout << ip[i];
            break;
        }
    }
    */
    char ipv4[255][16];
    std::string ip_ = "";
    std::ifstream file("IPv410.txt");
    int i = 0;
    int ind_ip = 0;
    if (!file.is_open()){
        printf("file is'nt open");
    }

    while (getline(file,ip_)){
        for (i = 14;ip_[i] != ':';++i){
            ipv4[ind_ip][i] = ip_[i];
        }
        ipv4[ind_ip][i] = '\0';
        ind_ip++;
    }
    file.close();
    for(int i = 0; i < 50; ++i)
        std::cout << ipv4[i] << std::endl;
}