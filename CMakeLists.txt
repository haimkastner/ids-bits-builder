cmake_minimum_required(VERSION 3.0)

# set the project name
project(ids-bits-builder)

# define the source
set(SOURCE main.cpp)

# add the executable for the current project with the defined sources and headers
add_executable(${PROJECT_NAME} ${SOURCE} src/ids_field.cpp src/ids_builder.cpp headers/bits_structures.h headers/constants.h headers/ids_builder.h headers/ids_field.h)

# add 'headers' directory to the 'include' directories
include_directories(${PROJECT_NAME} headers)