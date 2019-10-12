project(lesson1)

add_executable(lesson1 src/main.cpp)
target_link_libraries(lesson1 ${SDL2_LIBRARY} ${SDL_HELPER_LIBRARY})

install(TARGETS lesson1 RUNTIME DESTINATION ${BIN_DIR})