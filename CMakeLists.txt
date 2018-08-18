cmake_minimum_required(VERSION 3.12)

##
# Google Test Framework
##
# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

##
# Project
##
project(MatasanoCpp)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set( CMAKE_VERBOSE_MAKEFILE on )
add_executable(${PROJECT_NAME} tst/set1/challenge1.cpp tst/set1/challenge2.cpp src/xor/xor.hpp src/xor/xor.cpp tst/set1/challenge3.cpp src/text_evaluator.cpp src/text_evaluator.hpp src/xor/xor_decryptor.cpp src/xor/xor_decryptor.hpp tst/set1/challenge4.cpp tst/set1/challenge5.cpp src/xor/xor_encryptor.cpp src/xor/xor_encryptor.hpp src/repeating_key.cpp src/repeating_key.hpp tst/set1/challenge6.cpp src/crypto_functions.hpp src/xor/xor_breaker.cpp src/xor/xor_breaker.hpp tst/set1/challenge7.cpp src/crypto_functions.cpp tst/set1/challenge8.cpp src/ecb_detector.cpp src/ecb_detector.hpp src/tools_stl.hpp src/xor/padding.hpp src/padding.cpp tst/set2/challenge9.cpp)

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(BOTAN REQUIRED botan-2)

find_package(Boost REQUIRED)
include_directories(${BOTAN_INCLUDE_DIRS} ${BOOST_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${BOTAN_LIBRARIES} gtest_main)
#add_test(NAME example_test COMMAND example)