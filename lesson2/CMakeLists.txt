project(lesson2)

add_executable(lesson2 src/main.cpp)
target_link_libraries(lesson2 ${SDL2_LIBRARY} ${SDL_HELPER_LIBRARY})

install(TARGETS lesson2 RUNTIME DESTINATION ${BIN_DIR})