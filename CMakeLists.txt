cmake_minimum_required (VERSION 3.0)
project (cpp_leak_sample)

IF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    add_executable(cpp_leak_sample ./src/cpp_leak_sample.cpp)
ELSE ()
    add_compile_options(-std=c++11)
    add_compile_options(-fsanitize=address)
    add_compile_options(-fno-omit-frame-pointer)
    add_compile_options(-fdiagnostics-color=auto)

    add_compile_options(-O1)
    add_compile_options(-g)
    

    add_definitions(-D_GLIBCXX_DEBUG)

    add_executable(cpp_leak_sample ./src/cpp_leak_sample.cpp)
    target_link_libraries(cpp_leak_sample stdc++ m pthread rt m dl gcc_s gcc c gcc_s gcc)
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
