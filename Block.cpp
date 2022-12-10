
#include "Block.h"
#include "SHA2.h"
Block::Block(unsigned int idx, Data d, std::string ph) {
    _index = idx;
    _data = d.text;
    _prev_hash = ph;
    _hash = calculate_hash();
}

std::string Block::calculate_hash() {
    std::string s = _data + std::to_string(_index) + _prev_hash;
    std::cout << std::endl << "<<" << s << ">>" << std::endl;
    return hash_2(s.data()).str();
}

std::string Block::get_hash() {
    return _hash;
}

std::string Block::get_prev_hash() {
    return _prev_hash;
}
bool Block::is_hash_valid() {
    return _hash == calculate_hash();
}

unsigned int Block::get_index() {
    return _index;
}
