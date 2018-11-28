cmake_minimum_required(VERSION 3.12)
project(bs_uebung_template_v0_43)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(includes)
include_directories(obj)
include_directories(src)
include_directories(unittests)

add_executable(bs_uebung_template_v0_43
        includes/blockdevice.h
        includes/macros.h
        includes/myfs-info.h
        includes/myfs-structs.h
        includes/myfs.h
        includes/wrap.h
        obj/blockdevice.o
        obj/mkfs.myfs.o
        obj/mount.myfs.o
        obj/myfs.o
        obj/wrap.o
        src/blockdevice.cpp
        src/mkfs.myfs.cpp
        src/mount.myfs.c
        src/myfs.cpp
        src/wrap.cpp
        unittests/catch.hpp
        unittests/helper.cpp
        unittests/helper.hpp
        unittests/main.cpp
        unittests/test-blockdevice.cpp
        unittests/test-myfs.cpp
        CMakeLists.txt
        Makefile
        mkfs.myfs
        mount.myfs)
