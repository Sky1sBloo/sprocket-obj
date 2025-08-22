cmake_minimum_required(VERSION 3.5)

project(sprocket-obj)

file(GLOB_RECURSE SRC "src/*.cpp")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(sprocket-obj ${SRC})

target_include_directories(sprocket-obj PUBLIC src)
target_include_directories(sprocket-obj PRIVATE lib)
