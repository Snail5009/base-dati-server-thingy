cmake_minimum_required(VERSION 4.2)
project(db)

set(INC "${CMAKE_SOURCE_DIR}/../include")

add_subdirectory(dbsh)
add_subdirectory(cliente)
add_subdirectory(rete)
add_subdirectory(server)
add_subdirectory(tipi)
