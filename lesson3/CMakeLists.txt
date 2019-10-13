project(lesson3)

find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

add_executable(lesson3 src/main.cpp)
target_link_libraries(lesson3 ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL_HELPER_LIBRARY})
install(TARGETS lesson3 RUNTIME DESTINATION ${BIN_DIR})