project(lesson6)

find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIR})

add_executable(lesson6 src/main.cpp)
target_link_libraries(lesson6 ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY})
install(TARGETS lesson6 RUNTIME DESTINATION ${BIN_DIR})