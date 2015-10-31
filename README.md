# Typecasting #

\#static_cast \#dynamic_cast \#reinterpret_cast \#const_cast

[![Build Status](https://travis-ci.org/xpdu/cpp-cast.svg?branch=master)](https://travis-ci.org/xpdu/cpp-cast)

Check [main.cpp](main.cpp) for more type conversion examples!


## Requirements ##

In order to build this project you need something to be installed. I've just used these particular versions:

| Product | Version |
|---|---|
| [CMake](https://cmake.org/) | 2.8 |
| [GCC](https://gcc.gnu.org/) | 4.9 |
| [Boost](http://www.boost.org/) | 1.58 |

It also should be ok to build it against other versions with (almost) no changes.


## Build ##

By default just type:

    $ cmake CMakeLists.txt
    $ make

In order to use custom `Boost` installation type:

    $ cmake -D Boost_INCLUDE_DIR=/tmp/boost_1_58_0 CMakeLists.txt
    $ make

To use a different compiler:

    $ cmake -D CMAKE_C_COMPILER=gcc-4.9 -D CMAKE_CXX_COMPILER=g++-4.9 CMakeLists.txt
    $ make


## Run ##

    $ ./cpp-cast
