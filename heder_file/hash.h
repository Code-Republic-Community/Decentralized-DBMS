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

std::stringstream compression (uint32_t * w){
    uint32_t h0 = 0x6a09e667U;
    uint32_t h1 = 0xbb67ae85U;
    uint32_t h2 = 0x3c6ef372U;
    uint32_t h3 = 0xa54ff53aU;
    uint32_t h4 = 0x510e527fU;
    uint32_t h5 = 0x9b05688cU;
    uint32_t h6 = 0x1f83d9abU;
    uint32_t h7 = 0x5be0cd19U;
    uint32_t a, b, c ,d ,e , f, g, h;
    a = h0;
    b = h1;
    c = h2;
    d = h3;
    e = h4;
    f = h5;
    g = h6;
    h = h7;
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
        s1 = rightrotate(h4, 6) ^ rightrotate(h4, 11) ^ rightrotate(h4, 25);
        ch = (h4 & h5) ^ ((~h4) & h6);
        
        temp1 = h7 + s1 + ch + k[i] + w[i];
        
        s0 = rightrotate(h0, 2) ^ rightrotate(h0, 13) ^ rightrotate(h0, 22);
        maj = (h0 & h1) ^ (h0 & h2) ^ (h1 & h2);        
        temp2 = s0 + maj;        
        h7 = h6;
        h6 = h5;
        h5 = h4;
        h4 = h3 + temp1;
        h3 = h2;
        h2 = h1;
        h1 = h0;
        h0 = temp1 + temp2;
    }
    h0 = h0 + a;
    h1 = h1 + b; 
    h2 = h2 + c;
    h3 = h3 + d;
    h4 = h4 + e;
    h5 = h5 + f;
    h6 = h6 + g;
    h7 = h7 + h;
    std::stringstream ret_string ;
    ret_string << std::hex << h0 << h1 << h2 << h3 << h4 << h5 << h6 << h7;
    return ret_string;
}

std::stringstream hash_2(const char* str){
    
    unsigned int* w = new unsigned int[64];
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