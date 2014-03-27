cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)


project("Contribution:C")

set(mySourceFiles
    src/c101_Company.c
    src/c101_Print.c
    src/c101_Total.c
    src/c101_Vector.c
    src/c101_Cut.c
    src/c101_Subunit.c
    src/c101_Util.c
)

add_executable(c101 src/main.c ${mySourceFiles})

include_directories(include)


set(myGnuFlags "-Wall -Wextra -pedantic -pedantic-errors")

if(CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 ${myGnuFlags}")
endif()

