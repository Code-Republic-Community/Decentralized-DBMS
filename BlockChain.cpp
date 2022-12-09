//
// Created by yuri on 12/9/22.
//

#include "BlockChain.h"

BlockChain::BlockChain() {
    Block genesis = create_genesis_block();
    chain.push_back(genesis);
}

Block BlockChain::create_genesis_block() {
    Data data;
    data.text = "NULL";

    Block gen_block(0, data, "NULL");
    return gen_block;
}

Block BlockChain::get_last_block() {
    return chain.back();
}

void BlockChain::add_block(Data d) {
    unsigned int last_index = chain.size() - 1;
    Block new_block(last_index + 1, d, get_last_block().get_hash());
    chain.push_back(new_block);
}

bool BlockChain::is_chain_valid() {
    std::vector<Block> ::iterator it;
    int chain_length = (int)chain.size();
    for (it = chain.begin(); it != chain.end(); ++it) {
        Block current_block = *it;
        if (!current_block.is_hash_valid()) {
            return false;
        }
        if (chain_length > 1) {
            Block previous_block = *(it - 1);
            if (current_block.get_prev_hash() != previous_block.get_hash()) {
                return false;
            }
        }
    }
    return true;
}

int BlockChain::count_of_blocks() {
    return chain.size();
}
