cmake_minimum_required(VERSION 3.28)
project(testC++ VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

if (MSVC)
    add_compile_options(
        /GS-
        # /source-charset:utf8 /execution-charset:utf8
        "$<$<C_COMPILER_ID:MSVC>:/utf-8>"
        "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>"
    )
endif (MSVC)

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

# set(Torch_DIR "C:/libtorch/share/cmake/Torch/")
# find_package(Torch REQUIRED)
# if(TORCH_FOUND)
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")
#     target_include_directories(${PROJECT_NAME} PUBLIC ${TORCH_INCLUDE_DIRS})
#     target_link_libraries(${PROJECT_NAME} ${TORCH_LIBRARIES})
# endif()

# if(MSVC)
#     file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
#     add_custom_command(TARGET ${PROJECT_NAME}
#                     POST_BUILD
#                     COMMAND ${CMAKE_COMMAND} -E copy_if_different
#                     ${TORCH_DLLS}
#                     $<TARGET_FILE_DIR:${PROJECT_NAME}>)
# endif (MSVC)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 26)
