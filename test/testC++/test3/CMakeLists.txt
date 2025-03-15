cmake_minimum_required(VERSION 3.28)
project(testC++ VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

if (MSVC)
    add_compile_options(
        /GS-
        "$<$<C_COMPILER_ID:MSVC>:/utf-8>"
        "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>"
    )
endif (MSVC)

aux_source_directory(${PROJECT_BINARY_DIR}/../src SRC_LIST)
include_directories(${PROJECT_BINARY_DIR}/../include)

add_executable(${PROJECT_NAME}
    ${SRC_LIST}
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

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

#     if(MSVC)
#         file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
#         add_custom_command(TARGET ${PROJECT_NAME}
#                         POST_BUILD
#                         COMMAND ${CMAKE_COMMAND} -E copy_if_different
#                         ${TORCH_DLLS}
#                         $<TARGET_FILE_DIR:${PROJECT_NAME}>)
#     endif (MSVC)
# endif()

# include(FetchContent)
# FetchContent_Declare(SFML
#     GIT_REPOSITORY https://github.com/SFML/SFML.git
#     GIT_TAG 3.0.0
#     GIT_SHALLOW ON
#     EXCLUDE_FROM_ALL
#     SYSTEM)
# FetchContent_MakeAvailable(SFML)
# target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
# target_link_libraries(${PROJECT_NAME} PRIVATE ${SFML_LIBRARIES})

# set(SFML_DIR "C:/SFML-3.0.0/lib/cmake/SFML")
# find_package(SFML 3.0 COMPONENTS Graphics Window System REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE ${SFML_LIBRARIES})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 26)