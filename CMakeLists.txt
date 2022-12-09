cmake_minimum_required(VERSION 3.24)
project(Decentralized_DBMS)

set(CMAKE_CXX_STANDARD 17)

add_executable(Decentralized_DBMS main.cpp Block.cpp Block.h BlockChain.cpp BlockChain.h Data.h SHA2.h)
