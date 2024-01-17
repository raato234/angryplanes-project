cmake_minimum_required(VERSION 3.24)
project(AngryPlanes)
include_directories("src")

set(EXECUTABLE_NAME AngryPlanes)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES src/*.cpp)
add_executable(${EXECUTABLE_NAME} ${SOURCES})
set(BUILD_SHARED_LIBS FALSE)
include(FetchContent)
FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML
    GIT_TAG 2.6.x
)
FetchContent_Declare(
    box2d
    GIT_REPOSITORY https://github.com/erincatto/box2d.git
    GIT_TAG 9dc24a6fd4f32442c4bcf80791de47a0a7d25afb
)
FetchContent_MakeAvailable(sfml box2d)

target_link_libraries(${EXECUTABLE_NAME} sfml-graphics sfml-window sfml-audio sfml-network sfml-system box2d)

