cmake_minimum_required(VERSION 3.18)
project(daft-engine)

set(SFML_STATIC_LIBRARIES TRUE)
add_subdirectory(SFML)

file(GLOB_RECURSE SRCS src/*.cpp src/*.hpp)

add_executable(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)
target_include_directories(${PROJECT_NAME} PRIVATE src src/engine src/scenes src/scenes/flap)