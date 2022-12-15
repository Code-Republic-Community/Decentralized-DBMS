#include <fstream>
#include <iostream>
//
void delete_IPv4_txt(std::string num_3 = "11"){
    std::string command = "IPv4";
    command += num_3 + ".txt";
    system(command.c_str());
}
void delete_number(){
    system("rm number.txt");
}

void print_number(){
    std::ifstream file("number.txt");
    std::string word;
    if(!file.is_open()){
        printf("file is'nt open");
        return;
    }
    while(file >> word) { //take word and print
      std::cout << word << std::endl;
   }
   file.close();
}

void add_IPv4_txt(std::string ipv4_start = "11"){
    std::string penultimate_3_digits = "echo ' ";
    penultimate_3_digits += ipv4_start + " ' >> number.txt";
    system (penultimate_3_digits.c_str());
    std::string command = "for ip in $(seq 1 254); do ping -c 1 -W 1 192.168.";
    command +=  ipv4_start + ".$ip | grep 'ttl' ;done > IPv4";
    command += ipv4_start + ".txt";
    system (command.c_str());
}

void get_IP(char *ipv4[16],std::string file_name = "IPv411.txt"){
    std::string ip_ = "";
    std::ifstream file(file_name);
    int i = 0;
    if (!file.is_open()){
        printf("file is'nt open");
        return;
    }
    
    for(int ind_ip = 0;getline(file,ip_); ++ind_ip){
        for (i = 14;ip_[i] != ':';++i){
            ipv4[ind_ip][i] = ip_[i];
        }
        ipv4[ind_ip][i] = '\0';
    }
    file.close();
}
