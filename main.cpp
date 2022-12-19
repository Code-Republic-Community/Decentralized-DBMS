#include "BlockChain.h"
#include "boost/property_tree/json_parser.hpp"

int main() {
    BlockChain chain;   //created chain with genesis bloack
    std::cout << "============================================================" << std::endl;
    std::cout << "index: " << chain.get_last_block().get_index() << std::endl;
    std::cout << "hash:  " << chain.get_last_block().get_hash() << std::endl;
    std::cout << "previous hash: " << chain.get_last_block().get_prev_hash() << std::endl;
    std::cout << "count: " << chain.count_of_blocks() << std::endl;
    std::cout << "============================================================" << std::endl;
    //Create second block
    Data d1;
    d1.text = "Hello";
    chain.add_block(d1);
    std::cout << "index: " << chain.get_last_block().get_index() << std::endl;
    std::cout << "hash:  " << chain.get_last_block().get_hash() << std::endl;
    std::cout << "previous hash: " << chain.get_last_block().get_prev_hash() << std::endl;
    std::cout << "count: " << chain.count_of_blocks() << std::endl;
    std::cout << "============================================================" << std::endl;
    //Create third block
    Data d2;
    d2.text = "World";
    chain.add_block(d2);
    std::cout << "index: " << chain.get_last_block().get_index() << std::endl;
    std::cout << "hash:  " << chain.get_last_block().get_hash() << std::endl;
    std::cout << "previous hash: " << chain.get_last_block().get_prev_hash() << std::endl;
    std::cout << "count: " << chain.count_of_blocks() << std::endl;
    std::cout << "============================================================" << std::endl;
    Data d3;
    d3.text = "Vahe";
    chain.add_block(d3);
    std::cout << "index: " << chain.get_last_block().get_index() << std::endl;
    std::cout << "hash:  " << chain.get_last_block().get_hash() << std::endl;
    std::cout << "previous hash: " << chain.get_last_block().get_prev_hash() << std::endl;
    std::cout << "count: " << chain.count_of_blocks() << std::endl;
    std::cout << "============================================================" << std::endl;
    //chain.print_chain_blocks();
    chain.convert_chain_to_json();
}
