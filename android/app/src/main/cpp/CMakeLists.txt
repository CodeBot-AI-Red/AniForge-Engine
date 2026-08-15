cmake_minimum_required(VERSION 3.31.11)
project(aniforge-engine-native)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

# Core Engine
add_library(aniforge-core STATIC
    core/engine.cpp
)

target_include_directories(aniforge-core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Main native library
add_library(aniforge-engine SHARED
    aniforge_jni.cpp
)

target_link_libraries(aniforge-engine
    aniforge-core
)
