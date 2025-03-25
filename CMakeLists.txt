cmake_minimum_required(VERSION 3.10)
project(learnGUI)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories if needed
include_directories(vendors)

# Gather source files
file(GLOB SOURCES
    "src/*.cpp"
    "vendors/*/*.cpp"
)

if(WIN32)
    add_executable(learning WIN32 ${SOURCES})
else()
    add_executable(learning ${SOURCES})
endif()

# Link necessary libraries
target_link_libraries(learning
    opengl32
    glfw3
)