project(FooPlaying)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
set(CMAKE_EXE_LINKER_FLAGS "-m64 -static-libgcc -static-libstdc++ -static")
add_executable(${PROJECT_NAME} ${SRC_LIST})

