cmake_minimum_required(VERSION 3.0.0)

#use vcpkg
set(CMAKE_TOOLCHAIN_FILE "./vcpkg/scripts/buildsystems/vcpkg.cmake")

project(cpp-learn VERSION 0.1.0)
configure_file(cpp-learnConfig.h.in cpp-learnConfig.h)
include(CTest)
enable_testing()

add_executable(${PROJECT_NAME} main.cpp)

#include directories
target_include_directories(
    ${PROJECT_NAME} PUBLIC
    ${PROJECT_BINARY_DIR}
)

#add a library depending on option
option(USE_ADDER "A simple library for adding 2 floats." ON)
if(USE_ADDER)
    add_subdirectory(Adder)
endif()

add_subdirectory(external/glfw)
find_package(OpenGL REQUIRED)
find_package(OpenSSL REQUIRED)
target_link_libraries(${PROJECT_NAME} 
    adder 
    glfw
    OpenGL::GL
    OpenSSL::SSL
    OpenSSL::Crypto
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
