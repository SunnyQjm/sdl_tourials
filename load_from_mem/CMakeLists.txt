project(load_from_mem)

find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

add_executable(load_from_mem src/main.cpp)
target_link_libraries(load_from_mem ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL_HELPER_LIBRARY})
install(TARGETS load_from_mem RUNTIME DESTINATION ${BIN_DIR})