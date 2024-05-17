cmake_minimum_required(VERSION 3.23)
project(bude_sql)


# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_executable(${PROJECT_NAME} src/proxy/main.cpp src/proxy/proxy.cpp
        src/proxy/proxy.h
        src/bplus/bplus.cpp
        src/bplus/bplus.h)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/src/
        ${PROJECT_SOURCE_DIR}/src/proxy
        ${PROJECT_SOURCE_DIR}/src/model
)