cmake_minimum_required(VERSION 3.28)
project(testC++)

set(CMAKE_CXX_STANDARD 20)

# set(OpenCV_DIR C:/opencv/build)
# find_package(OpenCV REQUIRED)
# include_directories(${OpenCV_INCLUDE_LIBS})
# link_directories(${OpenCV_LIBS})

# find_package(Torch REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
# target_link_libraries(${PROJECT_NAME} "${OpenCV_LIBS}" "${TORCH_LIBRARIES}")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 26)
