cmake_minimum_required(VERSION 3.15)
project(ShoeShineShop)

set(CMAKE_CXX_STANDARD 14)

add_executable(ShoeShineShop main.cpp Model.h Model.cpp Shop.h Shop.cpp)
find_package(Threads REQUIRED)
target_link_libraries(ShoeShineShop Threads::Threads)