cmake_minimum_required(VERSION 3.16)

project(Hydra)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE HYDRA_SOURCES
    CONFIGURE_DEPENDS
    src/*.cpp
)

add_executable(hydra ${HYDRA_SOURCES})