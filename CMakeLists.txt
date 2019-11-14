cmake_minimum_required(VERSION 3.0)

# set the project name
project(ids-bits-builder)

# define the source
set(SOURCE main.cpp)

# add the executable for the current project with the defined source
add_executable(${PROJECT_NAME} ${SOURCE})
