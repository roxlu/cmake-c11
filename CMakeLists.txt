# -----------------------------------------------------------------

cmake_minimum_required(VERSION 3.19)
project(mylib C)
set(CMAKE_C_STANDARD 11)
set(src_dir ${CMAKE_CURRENT_LIST_DIR}/)

# -----------------------------------------------------------------

set(sources
  ${src_dir}/log.c
  )

add_library(rx STATIC ${sources})
target_link_libraries(rx -pthread)

# -----------------------------------------------------------------

add_executable(test test.c)
