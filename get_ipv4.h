//
// Created by yuri on 1/11/23.
//

#ifndef DECENTRALIZED_DBMS_GET_IPV4_H
#define DECENTRALIZED_DBMS_GET_IPV4_H

#include <fstream>
#include <iostream>

class my_IPv4{
public:
    char ipv4[255][16];
    char number[255][4];
    short count_ipv4;
    short count_number;
    void delete_IPv4_txt(std::string);
    void create_IPv4_txt(std::string);
    void get_IP(std::string);
    my_IPv4();
private:
    void get_number();
    void del_number(std::string);
    void substr_(std::string);
};

my_IPv4::my_IPv4() {
    for (int i = 0 ; i < 255 ;++i) {
        ipv4[i][0] = '\0';
        number[i][0] = '\0';
    }
    count_ipv4 = 0;
    count_number = 0;
}

void my_IPv4::del_number(std::string num_3) {
    if (number[0][0] == '\0')
        get_number();
    std::ifstream file("number.txt");
    std::string line;
    std::ofstream temp("temp.txt");
    if(!file.is_open() || !temp.is_open()) {
        printf("try again");
        return;
    }
    while (getline(file,line)) {
        if(line != num_3) {
            temp << line;
            temp << "\n";
        }
    }
    system("rm number.txt");
    system("mv temp.txt number.txt");
}

void my_IPv4::delete_IPv4_txt(std::string num_3 = "") {
    bool t = false;
    if (num_3 == ""){
        printf("penultimate digits of ip were not corrected");
        return;
    }
    if (number[0][0] == '\0')
        get_number();
    for (int i = 0; i < count_number;++i){
        if (num_3 == number[i]){
            t = true;
            break;
        }
    }
    if (t){
        std::string command = "rm IPv4";
        command += num_3 + ".txt";
        system(command.c_str());
        del_number(num_3);
    }else{
        printf("file not found");
    }
}

void my_IPv4::get_number() {
    std::ifstream file("number.txt");
    std::string word;
    int i;
    if(!file.is_open()){
        printf("file isn't open");
        return;
    }
    count_number = 0;
    while(file >> word) {
        for(i = 0; i < word.length();++i){
            if(word[i] != ' '){
                number[count_number][i] = word[i];
            }

        }
        number[count_number][i] = '\0';
        ++count_number;
    }
    file.close();
}

void my_IPv4::create_IPv4_txt(std::string ipv4_start = "") {
    bool t = true;
    if(ipv4_start == ""){
        printf("penultimate digits of ip were not corrected");
        return;
    }
    get_number();
    for (int i = 0; i < count_number;++i) {
        if(number[i] == ipv4_start){
            t = false;
            break;
        }
    }
    if(t){
        std::string penultimate_3_digits = "echo '";
        penultimate_3_digits += ipv4_start + "' >> number.txt";
        system (penultimate_3_digits.c_str());
    }
    std::string command = "for ip in $(seq 1 254); do ping -c 1 -W 1 192.168.";
    command +=  ipv4_start + ".$ip | grep 'ttl' ;done > IPv4";
    command += ipv4_start + ".txt";
    system (command.c_str());
}

void my_IPv4::substr_(std::string str){
    int j = 14;
    for (;str[j] != ':';++j)
    {
        ipv4[count_ipv4][j - 14] = str[j];
    }
    ipv4[count_ipv4][j - 14] = '\0';
}

void my_IPv4::get_IP(std::string number = ""){
    if (number == ""){
        printf("penultimate digits of ip were not corrected");
        return;
    }
    std::string file_name = "IPv4";
    file_name += number + ".txt";
    std::string ip_;
    std::ifstream file(file_name);
    if (!file.is_open()){
        printf("file isn't open");
        return;
    }
    count_ipv4 = 0;
    while (getline(file,ip_)){
        substr_(ip_);
        ++count_ipv4;
    }
    file.close();
}




#endif //DECENTRALIZED_DBMS_GET_IPV4_H
