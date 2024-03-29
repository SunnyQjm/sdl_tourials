cmake_minimum_required(VERSION 3.13)
project(sdl_tourials)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
set(BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# Bump up warning levels appropriately for clang, gcc & msvc and build in debug mode
if (MSVC)
    if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")
endif()

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
include_directories(include)
include_directories(helper)

#add_executable(sdl_tourials main.cpp)
#target_link_libraries(sdl_tourials ${SDL2_LIBRARY})
add_library(sdl_helper SHARED helper/SDL2Helper.cpp)
add_library(sdl_helper_static STATIC helper/SDL2Helper.cpp)
set_target_properties(sdl_helper_static PROPERTIES OUTPUT_NAME "sdl_helper")
GET_TARGET_PROPERTY (OUTPUT_VALUE sdl_helper_static OUTPUT_NAME)

MESSAGE (STATUS "This is the hello_static OUTPUT_NAME: " ${OUTPUT_VALUE})

INSTALL (TARGETS sdl_helper sdl_helper_static LIBRARY DESTINATION lib

        ARCHIVE DESTINATION lib)

INSTALL (FILES helper/SDL2Helper.h DESTINATION include/sdl_helper)

set(SDL_HELPER_LIBRARY sdl_helper)


add_subdirectory(lesson0)
add_subdirectory(lesson1)
add_subdirectory(lesson2)
add_subdirectory(lesson3)
add_subdirectory(lesson4)
add_subdirectory(lesson5)
add_subdirectory(lesson6)
add_subdirectory(load_from_mem)


if (NOT ${PROJECT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
    file(COPY "${PROJECT_SOURCE_DIR}/res" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()