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

void BlockChain::add_block(Data data) {
    unsigned int last_index = chain.size() - 1;
    Block new_block(last_index + 1, data, get_last_block().get_hash());
    chain.push_back(new_block);
}

bool BlockChain::is_chain_valid() {
    std::vector<Block>::iterator it;
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

void BlockChain::print_chain_blocks() {
    for(int i = 0; i<chain.size(); i++){
        std::cout<<"Index " << i << ": " << chain[i].get_index()<<std::endl;
        std::cout<<"Index " << i << ": " << chain[i].get_hash()<<std::endl;
        std::cout<<"Index " << i << ": " << chain[i].get_prev_hash()<<std::endl;
    }
}

void BlockChain::convert_chain_to_json() {
    int _index = 0;
    std::string i_data = std::to_string(_index) + ".data";
    std::string i_hash = std::to_string(_index) + ".hash";
    std::string i_prev_hash = std::to_string(_index) + ".previoushash";

    std::string _data = chain[_index].get_data();
    std::string _prev_hash = chain[_index].get_prev_hash();
    std::string _hash = chain[0].get_hash();

    std::ostringstream oss;
    oss << "{\"" << _index << "\":{\"data\":\"" << _data << "\",\"hash\":" << "\"" << _hash << "\"" << ",\"previoushash\":\"" << _prev_hash << "\"""}}";
    std::cout<<std::endl;
    std::string myString = oss.str();

    std::stringstream jsonEncodedData(myString);
    boost::property_tree::ptree rootHive;
    boost::property_tree::read_json(jsonEncodedData, rootHive);

    for(int i = 1; i<chain.size(); i++) {
        _index = i;
        i_data = std::to_string(_index) + ".data";
        i_hash = std::to_string(_index) + ".hash";
        i_prev_hash = std::to_string(_index) + ".previoushash";

        _data = chain[_index].get_data();
        _prev_hash = chain[_index].get_prev_hash();
        _hash = chain[_index].get_hash();

        rootHive.put(i_data, _data);
        rootHive.put(i_hash, _hash);
        rootHive.put(i_prev_hash, _prev_hash);
    }
    std::stringstream myJsonEncodedData(myString);
    boost::property_tree::write_json(myJsonEncodedData, rootHive);

    std::cout << myJsonEncodedData.str();

    //create .json file
    std::ofstream fs;
    fs.open("file.json");
    fs<<myJsonEncodedData.str();
    fs.close();
}