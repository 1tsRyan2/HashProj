cmake_minimum_required(VERSION 3.29)
project(HashProj)

set(CMAKE_CXX_STANDARD 20)

add_executable(HashProj
        HashMap.cpp
        HashMap.hpp
        HashNode.cpp
        HashNode.hpp
        MakeSeuss.cpp
        MakeSeuss.hpp
        mainHash.cpp
)
