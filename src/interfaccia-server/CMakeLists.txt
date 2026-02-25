
add_executable(interfaccia-server)
target_sources(interfaccia-server PRIVATE interfaccia-server.c)
target_link_libraries(interfaccia-server PRIVATE rete)
