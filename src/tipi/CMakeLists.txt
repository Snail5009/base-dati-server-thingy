add_library(tipi STATIC)
target_sources(tipi PRIVATE hashmap.c
PUBLIC FILE_SET HEADERS
BASE_DIRS ${INC}
FILES ${INC}/tipi/hashmap.h
)
