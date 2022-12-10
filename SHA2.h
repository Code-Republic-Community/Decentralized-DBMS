#ifndef DECENTRALIZED_DBMS_SHA2_H
#define DECENTRALIZED_DBMS_SHA2_H

#include <iostream>
#include <sstream>

#ifdef __linux__
#include <unistd.h>
#endif
#ifdef _WIN32
#include <windows.h>
#endif

void mySleep(int sleepMs)
{
#ifdef __unix__
    sleep(sleepMs);
#endif
#ifdef _WIN32
    Sleep(sleepMs*1000);
#endif
}

// hastatunner voronq vercvel en hesh algoriti arajin 8 parz tveri qarakusi amrnati amboxj mas@  heshavorelu ardyunqum
uint32_t s0, s1;
// hastatunner [2,311] mijakayqi parz tveric qarakusi armat hanac kotorakayin maseri 16 akan tesq@
uint32_t rightrotate(uint32_t word, short count)
{
    count -= int(count / 32) * 32;
    return (word >> count) | (word << (32 - count));
};

std::stringstream compression(uint32_t* w) {
    uint32_t h0 = 0x6a09e667;
    uint32_t h1 = 0xbb67ae85;
    uint32_t h2 = 0x3c6ef372;
    uint32_t h3 = 0xa54ff53a;
    uint32_t h4 = 0x510e527f;
    uint32_t h5 = 0x9b05688c;
    uint32_t h6 = 0x1f83d9ab;
    uint32_t h7 = 0x5be0cd19;
    uint32_t a, b, c, d, e, f, g, h;
    a = h0;
    b = h1;
    c = h2;
    d = h3;
    e = h4;
    f = h5;
    g = h6;
    h = h7;
    uint32_t k[] = { 0x428a2f98,  0x71374491,  0xb5c0fbcf,  0xe9b5dba5,
                     0x3956c25b,  0x59f111f1,  0x923f82a4,  0xab1c5ed5,  0xd807aa98,
                     0x12835b01,  0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe,
                     0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6,
                     0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
                     0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3,
                     0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138,
                     0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e,
                     0x92722c85, 0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
                     0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070, 0x19a4c116,
                     0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
                     0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814,
                     0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };
    uint32_t ch, temp1, temp2, maj;
    for (int i = 0; i < 64; ++i) {
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
    std::stringstream ret_string;
    ret_string << std::hex << h0 << h1 << h2 << h3 << h4 << h5 << h6 << h7;
    return ret_string;
};

std::stringstream hash_2(const char* str) {
    mySleep(5);
    uint32_t* w = new uint32_t[64];
    short counter = 4;
    short ind_w = 0;
    short ind_str = 0;
    for (; str[ind_str] != '\0';)
    {
        w[ind_w] = 0;
        if (!(ind_str % 4)) {
            counter = 4;
            while (counter--) {
                if (str[ind_str] != '\0') {
                    *(w + ind_w) <<= 8;
                    *(w + ind_w) += int(str[ind_str]);
                    ++ind_str;
                }
                else if (ind_str % 4) {
                    *(w + ind_w) <<= ((4 - (ind_str - (int(ind_str / 4) * 4))) * 8);
                    break;
                }
            }
        }
        ++ind_w;
    }
    if (ind_str % 4) {
        *(w + ind_w - 1) += (1 << 7);
    }
    else {
        *(w + ind_w) = 1;
        *(w + ind_w) <<= 31;
        ++ind_w;
    }
    for (; ind_w < 64; ++ind_w)
    {
        *(w + ind_w) = 0;
    }
    *(w + 15) = ind_str * 8;
    for (ind_w = 16; ind_w < 64; ++ind_w) {
        s0 = rightrotate(w[ind_w - 15], 7) ^ rightrotate(w[ind_w - 15], 18) ^ (w[ind_w - 15] >> 3);
        s1 = rightrotate(w[ind_w - 2], 17) ^ rightrotate(w[ind_w - 2], 19) ^ (w[ind_w - 2] >> 10);
        w[ind_w] = w[ind_w - 16] + s0 + w[ind_w - 7] + s1;
    }
    return compression(w);
};

#endif //DECENTRALIZED_DBMS_SHA2_H