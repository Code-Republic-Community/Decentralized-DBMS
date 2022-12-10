
#ifndef DECENTRALIZED_DBMS_BLOCKCHAIN_H
#define DECENTRALIZED_DBMS_BLOCKCHAIN_H

#include <iostream>
#include <vector>
#include "Block.h"
class BlockChain {

public:
    BlockChain();
    std::vector<Block> chain;
    bool is_chain_valid();
    void add_block(Data data);
    Block get_last_block();
    int count_of_blocks();
private:
    Block create_genesis_block();
};


#endif //DECENTRALIZED_DBMS_BLOCKCHAIN_H
