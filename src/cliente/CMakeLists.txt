add_library(cliente STATIC)
target_sources(cliente PRIVATE cliente.c
PUBLIC FILE_SET HEADERS
BASE_DIRS ${INC}
FILES ${INC}/rete/rete.h ${INC}/rete/protocollo.h
)
target_link_libraries(cliente PRIVATE rete)
