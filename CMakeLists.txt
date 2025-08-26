cmake_minimum_required(VERSION 3.22)
project(Pong)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

set(SOURCE_FILES
    main.cpp
    ${PROJECT_SOURCE_DIR}/lib/Ball.cpp
    ${PROJECT_SOURCE_DIR}/lib/Menu.cpp
    ${PROJECT_SOURCE_DIR}/lib/Net.cpp
    ${PROJECT_SOURCE_DIR}/lib/Paddle.cpp
    ${PROJECT_SOURCE_DIR}/lib/Score.cpp
)

include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(SFML COMPONENTS graphics window system audio REQUIRED)

add_executable(Pong ${SOURCE_FILES})

target_link_libraries(Pong sfml-graphics sfml-window sfml-system sfml-audio)