file(GLOB_RECURSE SOURCES "*.cpp")
list(FILTER SOURCES EXCLUDE REGEX ".*main.cpp$")

add_library(MehLib ${SOURCES})

add_executable(Meh main.cpp)
target_link_libraries(Meh MehLib)