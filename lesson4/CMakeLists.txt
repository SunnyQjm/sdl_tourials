project(lesson4)

find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

add_executable(lesson4 src/main.cpp)
target_link_libraries(lesson4 ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})
install(TARGETS lesson4 RUNTIME DESTINATION ${BIN_DIR})