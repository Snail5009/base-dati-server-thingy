
add_executable(server)
target_sources(server PRIVATE server.c clienti.c)
target_link_libraries(server PRIVATE rete)
