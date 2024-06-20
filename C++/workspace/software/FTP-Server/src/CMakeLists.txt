cmake_minimum_required(VERSION 3.28)
project(FTP-Server)

set(CMAKE_CXX_STANDARD 20)

aux_source_directory(${PROJECT_BINARY_DIR}/../src SRC_LIST)
include_directories(${PROJECT_BINARY_DIR}/../include)

add_executable(${PROJECT_NAME}
    ${SRC_LIST}
)

# set(OpenCV_DIR "C:/opencv/build/x64/vc16/lib")
# find_package(OpenCV REQUIRED)
# if(OpenCV_FOUND)
#     target_include_directories(${PROJECT_NAME} PUBLIC ${OpenCV_INCLUDE_DIRS})
#     target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
 
# endif()

# set(CMAKE_PREFIX_PATH "C:/libtorch-2.2.2+cu121")
# find_package(Torch REQUIRED)
# if(TORCH_FOUND)
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")
#     target_include_directories(${PROJECT_NAME} PUBLIC ${TORCH_INCLUDE_DIRS})
#     target_link_libraries(${PROJECT_NAME} ${TORCH_LIBRARIES})

# endif()

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 26)
