//
// Created by yuri on 12/9/22.
//

#ifndef DECENTRALIZED_DBMS_BLOCK_H
#define DECENTRALIZED_DBMS_BLOCK_H

#pragma once
#include <iostream>
#include "Data.h"

class Block {

public:
    Block(unsigned int idx, Data d, std::string prev_hash);
    std::string get_hash();
    std::string get_prev_hash();
    unsigned int get_index();
    std::string calculate_hash();
    bool is_hash_valid();

private:
    unsigned int _index;
    std::string _data;
    std::string _hash;
    std::string _prev_hash;

};

#endif //DECENTRALIZED_DBMS_BLOCK_H
