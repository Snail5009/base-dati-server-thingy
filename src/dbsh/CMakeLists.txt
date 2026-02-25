
add_executable(dbsh)
target_sources(dbsh PRIVATE dbsh.c)
target_link_libraries(dbsh PRIVATE cliente)
