# //why version 3.24 only ?? becoz it's earlier versions are clumpier
cmake_minimum_required(VERSION 3.24) 


project(exchange LANGUAGES CXX)


# //fetch content is modern dependency mechanism, it will clone an external git repository during configuration.
include(FetchContent)


# //set C++ standard
# //deliberately using C++ standard 20 features

set(CMAKE_CXX_STANDARD 20)

# //below means if compiler fails in any of the feature of C++ 20, so it should fail loudly not silently

set(CMAKE_CXX_STANDARD_REQUIRED ON)

# C++ 20 will not follow any other external oficial rules/extensions
set(CMAKE_CXX_EXTENSIONS OFF)

# 
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# below means we are including the file cmake/dependencies.cmake
# list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
# include(Dependencies)


# adding library - this line will shape everything of project it's structure basically
add_library(exchange_project INTERFACE)  

target_include_directories(
    exchange_project
    INTERFACE 
      "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

# compile features
target_compile_features(exchange_project INTERFACE cxx_std_20)

target_compile_options(
exchange_project
INTERFACE

# wall stands for warnings all - ununsed var, signed/unsigned value
 -Wall 

#  it will add more like empty bodies, unused parameters, suspicious comparishons
 -Wextra 

#  we warn on anything that usesnon standard C++ features. it will make non -standard C++ features off
 -Wpedantic 
 
# disabling C++ exceptions like throw, catch - mechanism for error catch
 -fno-exceptions
)

# main cpp file - one source file
add_executable(
  exchange 
  src/exchange_main.cpp
) 

# this exchange we have need to link with our project
target_link_libraries( 
    exchange 
    PRIVATE 
      exchange_project
)

# exhange we hv it's having these properties
set_target_properties( 
    exchange 
    PROPERTIES 
    OUTPUT_NAME "exchange"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/src"
)



# trader_terminal
add_executable (
    trader_terminal
    tools/trader_terminal.cpp
)

target_link_libraries(
    trader_terminal
    PRIVATE 
     exchange_project
)

set_target_properties(
    trader_terminal 
    PROPERTIES 
    OUTPUT_NAME "trader_terminal"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tools"
)


# liquidity_bot
add_executable( 
    liquidity_bot
    tools/liquidity_bot.cpp
)

target_link_libraries(
    liquidity_bot
    PRIVATE 
     exchange_project
) 

set_target_properties(
    liquidity_bot 
    PROPERTIES
     OUTPUT_NAME "Liquidity_bot"
     RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tools"
)