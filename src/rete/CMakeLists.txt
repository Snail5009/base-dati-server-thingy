
set(INC "${CMAKE_SOURCE_DIR}/../include")

add_library(rete STATIC)
target_sources(rete PRIVATE rete.c
PUBLIC FILE_SET HEADERS
BASE_DIRS ${INC}
FILES ${INC}/rete/rete.h
)
