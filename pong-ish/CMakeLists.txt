cmake_minimum_required(VERSION 3.1)
project(pong-ish)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "$ENV{SFML_ROOT}/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

include_directories($ENV{SFML_ROOT}/include/ include/)

set(HEADERS
            include/game.hpp)

set(SOURCES
            src/main.cpp
            src/game.cpp)

source_group("Headers" FILES ${HEADERS})
source_group("Sources" FILES ${SOURCES})

add_executable(pong-ish ${SOURCES} ${HEADERS})

target_link_libraries(pong-ish sfml-graphics sfml-audio)
