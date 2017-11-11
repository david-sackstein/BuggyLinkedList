cmake_minimum_required(VERSION 3.8)
project(BuggyLinkedList)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES BuggyLinkedList.c)
add_executable(BuggyLinkedList ${SOURCE_FILES})