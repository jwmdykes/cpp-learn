cmake_minimum_required(VERSION 3.0.0)

#use vcpkg
set(CMAKE_TOOLCHAIN_FILE "./vcpkg/scripts/buildsystems/vcpkg.cmake")

project(cpp-learn VERSION 0.1.0)
include(CTest)
enable_testing()

#add a library depending on option
option(USE_ADDER "A simple library for adding 2 floats." NO)
if(USE_ADDER)
    add_subdirectory(Adder)
    list(APPEND EXTRA_LIBS adder)
endif()

add_executable(${PROJECT_NAME} main.cpp)

#include directories
target_include_directories(
    ${PROJECT_NAME} PUBLIC
    ${PROJECT_BINARY_DIR}
)
configure_file(cpp-learnConfig.h.in cpp-learnConfig.h)

add_subdirectory(external/glfw)
find_package(OpenGL REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(GLEW REQUIRED)

target_link_libraries(${PROJECT_NAME} 
    glfw
    OpenGL::GL
    OpenSSL::SSL
    OpenSSL::Crypto
    GLEW::GLEW
    ${EXTRA_LIBS}
)

install(
    TARGETS ${PROJECT_NAME}
    RUNTIME
    DESTINATION bin
    COMPONENT applications
)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
