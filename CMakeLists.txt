cmake_minimum_required(VERSION 3.14)
include(FetchContent)

project(sprocket-obj)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Options
option(BUILD_GUI "Builds program with gui" OFF)

add_subdirectory(src/importer)

if(BUILD_GUI)

FetchContent_Declare(
  wxWidgets
  GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
  GIT_TAG        v3.2.6   # or a specific commit/tag
)
FetchContent_MakeAvailable(wxWidgets)
file(GLOB_RECURSE SRC "src/gui/*.cpp")
add_executable(sprocket-obj ${SRC})
target_link_libraries(sprocket-obj PRIVATE wx::core wx::base)
target_link_directories(sprocket-obj PRIVATE src/gui)

else()

add_executable(sprocket-obj src/main-terminal.cpp)

endif()

target_link_libraries(sprocket-obj PRIVATE sprocket-importer)

