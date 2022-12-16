#include <fstream>
#include <iostream>
//
int size_ipv4 = 0;
void delete_IPv4_txt(std::string num_3 = ""){
    if(num_3 == "")
        return;
    std::string command = "IPv4";
    command += num_3 + ".txt";
    system(command.c_str());
}

void print_number(){
    std::ifstream file("number.txt");
    std::string word;
    if(!file.is_open()){
        printf("file isn't open");
        return;
    }
    while(file >> word) {
        std::cout<< word;
   }
   file.close();
}

bool is_the_number_here(std::string num_3 = ""){
    std::ifstream file1("number.txt");
    std::string num;
    if (!file1.is_open()){
        printf("number file is'nt open in bool function");
        return false;
    }
    while(getline(file1,num)){
        if (num == num_3){
            file1.close();
            return true;
        }
    }
    file1.close();
    return true;
}

void create_IPv4_txt(std::string ipv4_start = ""){
    if(ipv4_start == ""){

    }
        return;
    if (!is_the_number_here()) {
        std::string penultimate_3_digits = "echo '";
        penultimate_3_digits += ipv4_start + "' >> number.txt";
        system (penultimate_3_digits.c_str());
    }
    std::string command = "for ip in $(seq 1 254); do ping -c 1 -W 1 192.168.";
    command +=  ipv4_start + ".$ip | grep 'ttl' ;done > IPv4";
    command += ipv4_start + ".txt";
    system (command.c_str());
}

void substr_(std::string str,char * ret_s){
    int j = 14;
    for (;str[j] != ':';++j)
    {
        ret_s[j - 14] = str[j]; 
    }
    ret_s[j - 14] = '\0';
}

void get_IP(char ipv4[255][16],std::string number = ""){
    if (number == ""){
        printf("penultimate digits of ip were not corrected");
        return;
    }
    std::string file_name = "IPv4";
    file_name += number + ".txt";
    std::string ip_;
    std::ifstream file(file_name);
    if (!file.is_open()){
        printf("file is'nt open");
    }
    size_ipv4 = 0;
    while (getline(file,ip_)){
        substr_(ip_,ipv4[size_ipv4]);
        ++size_ipv4;
    }
    file.close();  
}
