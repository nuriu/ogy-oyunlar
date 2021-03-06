cmake_minimum_required(VERSION 3.1)
project(pong-ish)

if (WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
    set(SFML_DIR "$ENV{SFML_ROOT}/lib/cmake/SFML")
endif (WIN32)

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

if (WIN32)
    include_directories($ENV{SFML_ROOT}/include/ include/)
else()
    include_directories(include/)
endif (WIN32)

set(HEADERS
            include/game.hpp
            include/paddle.hpp)

set(SOURCES
            src/main.cpp
            src/game.cpp
            src/paddle.cpp)

source_group("Headers" FILES ${HEADERS})
source_group("Sources" FILES ${SOURCES})

add_executable(pong-ish ${SOURCES} ${HEADERS})

target_link_libraries(pong-ish sfml-graphics sfml-audio)
