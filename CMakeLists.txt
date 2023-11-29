cmake_minimum_required(VERSION 3.26)
project(EhallCpp)

set(CMAKE_CXX_STANDARD 20)
set (OPENSSL_USE_STATIC_LIBS TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm/bin/clang++")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmodules")

find_package (OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)

add_library(ehallcpplib
  STATIC
  src/login.cpp
  src/queryinfo.cpp
)
target_include_directories(ehallcpplib
  PUBLIC
  include
)
target_link_libraries (ehallcpplib OpenSSL::SSL OpenSSL::Crypto ZLIB::ZLIB ${CMAKE_DL_LIBS})

add_executable (ehallapp 
  apps/main.cpp
)
target_include_directories(ehallapp
  PUBLIC
  include
)
target_link_libraries (ehallapp ehallcpplib)
