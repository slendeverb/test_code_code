cmake_minimum_required(VERSION 3.14)

project(testC++ LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fopenmp")

add_definitions(-DNOMINMAX)

include_directories(
        ${PROJECT_SOURCE_DIR}/include
)

# 查找当前目录下的所有源文件，并将名称保存到 SRC_LIST 变量
file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# 将源代码添加到此项目的可执行文件。
add_executable(${PROJECT_NAME}
        ${SRC_LIST}
        ${BACKWARD_ENABLE}
)

find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC Threads::Threads)

find_package(OpenMP REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC OpenMP::OpenMP_CXX)

find_path(FASTIO_INCLUDE_DIRS "fast_io.h")
target_include_directories(${PROJECT_NAME} PRIVATE ${FASTIO_INCLUDE_DIRS})

find_package(fmt CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)

find_package(range-v3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE range-v3::meta range-v3::concepts range-v3::range-v3)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

find_package(Backward CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Backward::Backward)
add_definitions(-DBACKWARD_HAS_DW=1)

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
find_package(glad CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)

find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
     target_include_directories(${PROJECT_NAME} PUBLIC ${OpenCV_INCLUDE_DIRS})
     target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})
endif()

find_package(SFML COMPONENTS Network Graphics Window Audio System CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Network SFML::Graphics SFML::Window SFML::Audio SFML::System)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Charts REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
     Qt${QT_VERSION_MAJOR}::Core
     Qt${QT_VERSION_MAJOR}::Widgets
     Qt${QT_VERSION_MAJOR}::Network
     Qt${QT_VERSION_MAJOR}::Charts
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    cmake_host_system_information(RESULT CPU_NUMBER_OF_LOGICAL_CORES QUERY NUMBER_OF_LOGICAL_CORES)
    add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP${CPU_NUMBER_OF_LOGICAL_CORES}>)
    target_compile_options(${PROJECT_NAME} PUBLIC
            /EHsc
    )
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(${PROJECT_NAME} PUBLIC
#            -march=native
#            -ffast-math
    )
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(${PROJECT_NAME} PUBLIC
    )
endif()