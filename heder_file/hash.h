#include <iostream>
#include <sstream>
// hastatunner voronq vercvel en hesh algoriti arajin 8 parz tveri qarakusi amrnati amboxj mas@  heshavorelu ardyunqum
uint32_t s0, s1;
// hastatunner [2,311] mijakayqi parz tveric qarakusi armat hanac kotorakayin maseri 16 akan tesq@ 
int rightrotate(uint32_t word, short count)
{
    count -=  int(count/32) * 32;
    return (word >> count)|(word << (32 - count));
}

std::string push_0(std::string str, int size){
    std::string ret_str = "00000000";
    const int size_ = 8;
    int count_0;
    count_0 = size_ - size;
    for (int i = 0; i < size;++i){
        ret_str[count_0 + i] =  str[i];
    }
    return ret_str;
}

std::stringstream compression (uint32_t * w){
    
    const int size_hash = 8;
    uint32_t hash[size_hash];
    hash[0] = 0x6a09e667U;
    hash[1] = 0xbb67ae85U;
    hash[2] = 0x3c6ef372U;
    hash[3] = 0xa54ff53aU;
    hash[4] = 0x510e527fU;
    hash[5] = 0x9b05688cU;
    hash[6] = 0x1f83d9abU;
    hash[7] = 0x5be0cd19U;
    uint32_t hash_cpy[8];
    hash_cpy[0] = hash[0];
    hash_cpy[1] = hash[1];
    hash_cpy[2] = hash[2];
    hash_cpy[3] = hash[3];
    hash_cpy[4] = hash[4];
    hash_cpy[5] = hash[5];
    hash_cpy[6] = hash[6];
    hash_cpy[7] = hash[7];
    uint32_t k[64] = {0x428a2f98U, 0x71374491U, 0xb5c0fbcfU, 0xe9b5dba5U,
        0x3956c25bU, 0x59f111f1U, 0x923f82a4U, 0xab1c5ed5U, 0xd807aa98U,
        0x12835b01U, 0x243185beU, 0x550c7dc3U, 0x72be5d74U, 0x80deb1feU,
        0x9bdc06a7U, 0xc19bf174U, 0xe49b69c1U, 0xefbe4786U, 0x0fc19dc6U,
        0x240ca1ccU, 0x2de92c6fU, 0x4a7484aaU, 0x5cb0a9dcU, 0x76f988daU,
        0x983e5152U, 0xa831c66dU, 0xb00327c8U, 0xbf597fc7U, 0xc6e00bf3U, 
        0xd5a79147U, 0x06ca6351U, 0x14292967U, 0x27b70a85U, 0x2e1b2138U, 
        0x4d2c6dfcU, 0x53380d13U, 0x650a7354U, 0x766a0abbU, 0x81c2c92eU, 
        0x92722c85U, 0xa2bfe8a1U, 0xa81a664bU, 0xc24b8b70U, 0xc76c51a3U, 
        0xd192e819U, 0xd6990624U, 0xf40e3585U, 0x106aa070U, 0x19a4c116U, 
        0x1e376c08U, 0x2748774cU, 0x34b0bcb5U, 0x391c0cb3U, 0x4ed8aa4aU, 
        0x5b9cca4fU, 0x682e6ff3U, 0x748f82eeU, 0x78a5636fU, 0x84c87814U,
        0x8cc70208U, 0x90befffaU, 0xa4506cebU, 0xbef9a3f7U, 0xc67178f2U
    };
    uint32_t ch,temp1,temp2,maj;
    for (int i = 0; i < 64; ++i){
        s1 = rightrotate(hash[4], 6) ^ rightrotate(hash[4], 11) ^ rightrotate(hash[4], 25);
        ch = (hash[4] & hash[5]) ^ ((~hash[4]) & hash[6]);
        
        temp1 = hash[7] + s1 + ch + k[i] + w[i];
        
        s0 = rightrotate(hash[0], 2) ^ rightrotate(hash[0], 13) ^ rightrotate(hash[0], 22);
        maj = (hash[0] & hash[1]) ^ (hash[0] & hash[2]) ^ (hash[1] & hash[2]);        
        temp2 = s0 + maj;        
        hash[7] = hash[6];
        hash[6] = hash[5];
        hash[5] = hash[4];
        hash[4] = hash[3] + temp1;
        hash[3] = hash[2];
        hash[2] = hash[1];
        hash[1] = hash[0];
        hash[0] = temp1 + temp2;
    }
    
    hash[0] = hash[0] + hash_cpy[0];
    hash[1] = hash[1] + hash_cpy[1]; 
    hash[2] = hash[2] + hash_cpy[2];
    hash[3] = hash[3] + hash_cpy[3];
    hash[4] = hash[4] + hash_cpy[4];
    hash[5] = hash[5] + hash_cpy[5];
    hash[6] = hash[6] + hash_cpy[6];
    hash[7] = hash[7] + hash_cpy[7];
    std::stringstream ret_string;
    std::stringstream temp;
    std::string temp_string;
    for (int i = 0; i < size_hash;++i){
        temp.str("");
        temp << std::hex << hash[i];
        temp_string = temp.str();
        temp_string = push_0(temp_string,temp_string.length());
        ret_string << temp_string;
    }
    //ret_string << std::hex << hash[0] << hash[1] << hash[2] << hash[3] << hash[4] << hash[5] << hash[6] << hash[7];
    return ret_string;
}

std::stringstream hash_2(const char* str){
    uint32_t* w = new uint32_t[64];
    short counter = 4;
    short ind_w = 0;
    short ind_str = 0;
    short full_in_32;
    for (;str[ind_str] != '\0';)
    {
        w[ind_w] = 0;
        if (!(ind_str  % 4)){
            counter = 4;
            while(counter--){
                if(str[ind_str] != '\0'){
                    *(w + ind_w) <<= 8;
                    *(w + ind_w) += int(str[ind_str]);
                    ++ind_str;
                }
            }
        }
        ++ind_w;
    }
    if ((w[ind_w - 1] >> 8) == 0)
        full_in_32 = 8;
    else if ((w[ind_w - 1] >> 16) == 0)
        full_in_32 = 16;
    else if ((w[ind_w - 1] >> 24) == 0)
        full_in_32 = 24;
    else 
        full_in_32 = 32;
    if (full_in_32 == 32){
        w[ind_w] += 1;
        w[ind_w] <<= full_in_32 - 1;
    }
    else{
        w[ind_w - 1] <<= 1;
        w[ind_w - 1] += 1;
        w[ind_w - 1] <<= (32 - full_in_32 - 1);
    }
    for (;ind_w < 64;++ind_w)
    {
        *(w  + ind_w) = 0;
    }    
    
    *(w + 15) = ind_str * 8;
    
    for (ind_w = 16;ind_w < 64;++ind_w){
        s0 = rightrotate(w[ind_w - 15],7) ^ rightrotate(w[ind_w - 15],18) ^ (w[ind_w - 15] >> 3);
        s1 = rightrotate(w[ind_w - 2],17) ^ rightrotate(w[ind_w - 2],19) ^ (w[ind_w - 2] >> 10);
        w[ind_w] = w[ind_w-16] + s0 + w[ind_w - 7] + s1;
    }
    return compression(w);
}