CMAKE_MINIMUM_REQUIRED(VERSION 3.4.1)

PROJECT(native_app)

FILE(GLOB sources ../*.cpp ../**/*.cpp)

ADD_LIBRARY(native_app ${sources})
