cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)

project("ContributionC")
enable_testing()

set(mySourceFiles
    src/c101_Company.c
    src/c101_Cut.c
    src/c101_Depth.c
    src/c101_Equal.c
    src/c101_Median.c
    src/c101_Print.c
    src/c101_Subunit.c
    src/c101_Test.c
    src/c101_Total.c
    src/c101_Util.c
    src/c101_Vector.c
    src/c101_Visit.c
)

function(c101_add_test title)
    add_executable(${title} "test/${title}.c")
    target_link_libraries(${title} ${EXPAT_LIBRARIES} 101)
    add_test(${title} ${title})
endfunction()

include_directories(include ${EXPAT_INCLUDE_DIRS})

add_library(101 SHARED ${mySourceFiles})
target_link_libraries(101 ${EXPAT_LIBRARIES})

add_executable(c101 src/main.c ${mySourceFiles})
target_link_libraries(c101 ${EXPAT_LIBRARIES})

c101_add_test(totalTest)
c101_add_test(cutTest)
c101_add_test(medianTest)
c101_add_test(depthTest)
c101_add_test(equalTest)

set(myGnuFlags "-Wall -Wextra -Wshadow -pedantic -pedantic-errors")

if(CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 ${myGnuFlags}")
endif()

