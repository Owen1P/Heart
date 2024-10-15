cmake_minimum_required(VERSION 3.0.0)
project(ascii_heart VERSION 0.1.0 LANGUAGES C)

add_executable(heart heart.c)
if (UNIX)
  target_link_libraries(heart m)
endif (UNIX)
