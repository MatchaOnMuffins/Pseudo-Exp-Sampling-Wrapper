CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(Pseudo_Exp_Sampling)

SET(CMAKE_C_STANDARD 99)

# glob all source files in src directory
FILE(GLOB_RECURSE SOURCE_FILES src/*.c)

# include directories
include_directories(includes)

# if osx
IF (APPLE)
    # configure for x86_64 and arm64
    SET(CMAKE_OSX_ARCHITECTURES "x86_64;arm64")
ENDIF (APPLE)

# if windows
IF (WIN32)
    SET(CMAKE_GENERATOR_PLATFORM "x86_64")
ENDIF (WIN32)

# add library
add_library(Pseudo_Exp_Sampling SHARED ${SOURCE_FILES})

# add executable
add_executable(Pseudo_Exp_Sampling_Exe main.c)

# link libraries
target_link_libraries(Pseudo_Exp_Sampling_Exe Pseudo_Exp_Sampling)
