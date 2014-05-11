Implementation for [101 Companies](http://101companies.org/), see http://101companies.org/wiki/Contribution:c for details.

Building
--------

This application manages its build process using [CMake](http://www.cmake.org/). It also requires a C11 capable compiler and [Lua 5.1](http://www.lua.org/). Once all these requirements are met, change into the root directory and run the following commands:

    mkdir build
    cd build
    cmake ..
    make

To run it, use `./c101`.
