cmake_minimum_required(VERSION 3.26)
project(ehallcpp)

set(CMAKE_CXX_STANDARD 11)
set (OPENSSL_USE_STATIC_LIBS TRUE)
find_package (OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)


add_executable (${PROJECT_NAME} main.cpp)
target_link_libraries (${PROJECT_NAME} OpenSSL::SSL OpenSSL::Crypto ZLIB::ZLIB ${CMAKE_DL_LIBS})