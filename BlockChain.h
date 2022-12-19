#ifndef DECENTRALIZED_DBMS_BLOCKCHAIN_H
#define DECENTRALIZED_DBMS_BLOCKCHAIN_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "Block.h"
#include <cstdlib>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <fstream>

class BlockChain {
public:
    BlockChain();
    std::vector<Block> chain;
    bool is_chain_valid();
    void add_block(Data data);
    Block get_last_block();
    int count_of_blocks();
    void print_chain_blocks();
    void convert_chain_to_json();
private:
    Block create_genesis_block();
};

#endif //DECENTRALIZED_DBMS_BLOCKCHAIN_H