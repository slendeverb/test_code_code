cmake_minimum_required(VERSION 3.28)
project(FTP-Client VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(
    /GS-
    # /source-charset:utf8 /execution-charset:utf8
)

aux_source_directory(${PROJECT_BINARY_DIR}/../src SRC_LIST)
include_directories(${PROJECT_BINARY_DIR}/../include)

add_executable(${PROJECT_NAME}
    ${SRC_LIST}
)

include(CTest)
enable_testing()

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 26)
