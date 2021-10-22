# mkdir build;cd build
# cmake .. -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++

cmake_minimum_required (VERSION 3.0)
project (cpp_leak_sample)

IF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    add_compile_options(/w44819)
	
    add_definitions(-DWIN32)
    add_definitions(-DWIN32_LEAN_AND_MEAN)
    add_definitions(-DNOMINMAX)
    add_definitions(-D_WINSOCK_DEPRECATED_NO_WARNINGS)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-D_WIN32_WINNT=0x0601)
    add_definitions(-D_SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING)
    add_definitions(-D_USE_MATH_DEFINES)
	
    add_executable(cpp_leak_sample ./src/cpp_leak_sample.cpp)
ELSE ()
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -ggdb -DNDEBUG -Wall -Wextra -fno-omit-frame-pointer -fdiagnostics-color=auto -std=c++17 ")

    add_executable(cpp_leak_sample ./src/cpp_leak_sample.cpp)
    link_libraries(stdc++fs)
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
