cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)


project("Contribution:C")

set(mySourceFiles
    src/c101_Company.c
    src/c101_Cut.c
    src/c101_Depth.c
    src/c101_Equal.c
    src/c101_Median.c
    src/c101_Parsing.c
    src/c101_Print.c
    src/c101_Subunit.c
    src/c101_Total.c
    src/c101_Unparsing.c
    src/c101_Util.c
    src/c101_Vector.c
    src/c101_Visit.c
)

add_executable(c101 src/main.c ${mySourceFiles})
find_package(Lua51 REQUIRED)
include_directories(include ${LUA_INCLUDE_DIR})
target_link_libraries(c101 ${LUA_LIBRARY})

file(COPY ${CMAKE_SOURCE_DIR}/sample.lua    DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/dumper.lua    DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/unparsing.lua DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/dkjson.lua    DESTINATION ${CMAKE_BINARY_DIR})

set(myGnuFlags "-Wall -Wextra -Wshadow -pedantic -pedantic-errors")

if(CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 ${myGnuFlags}")
endif()

