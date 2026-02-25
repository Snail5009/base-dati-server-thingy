
add_executable(interfaccia-cliente)
target_sources(interfaccia-cliente PRIVATE interfaccia-cliente.c)
target_link_libraries(interfaccia-cliente PRIVATE rete)
