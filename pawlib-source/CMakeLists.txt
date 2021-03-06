# CMake Config for Executable (MousePaw Media Build System)
# Version: 2.1.0
# Tailored For: Anari
#
# Author(s): Jason C. McDonald

# LICENSE
# Copyright (c) 2018 MousePaw Media.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice,
# this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
# this list of conditions and the following disclaimer in the documentation
# and/or other materials provided with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its contributors
# may be used to endorse or promote products derived from this software without
# specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
# THE POSSIBILITY OF SUCH DAMAGE.
#
# CONTRIBUTING
# See https://www.mousepawmedia.com/developers for information
# on how to contribute to our projects.

# Specify the verison being used.
cmake_minimum_required(VERSION 3.1)

# CHANGEME: Name your project here
project("PawLIB")
set(TARGET_NAME "pawlib")

message("Using ${CONFIG_FILENAME}.config")
include(${CMAKE_HOME_DIRECTORY}/../${CONFIG_FILENAME}.config)

# Compiler and Version check...
# Allow Clang 3.4
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "3.4")
        message(FATAL_ERROR "Clang is too old. >= v3.4 required. Aborting build.")
    endif()
    set(COMPILERTYPE "clang")
    message("Clang 3.4 or later detected. Proceeding...")
# Allow AppleClang
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "5")
        message(FATAL_ERROR "Clang is too old. >= v5.x required. Aborting build.")
    endif()
    set(COMPILERTYPE "clang")
# Allow GCC 5.x
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "5")
        message(FATAL_ERROR "GCC is too old. >= v5.x required. Aborting build.")
    endif()
    set(COMPILERTYPE "gcc")
    message("GCC 5.x or later detected. Proceeding...")
# Allow compilers that simulate GCC 5.x.
elseif(CMAKE_CXX_SIMULATE_ID STREQUAL "GNU")
    if(CMAKE_CXX_SIMULATE_VERSION VERSION_LESS "5")
        message(FATAL_ERROR "Not simulating GCC 5.x. Aborting build.")
    endif()
    set(COMPILERTYPE "gcc")
    message("GCC (5.x or later) simulation detected. Proceeding...")
else()
    message(FATAL_ERROR "Not using or simulating a compatible compiler (minimum GCC 5.x, Clang 3.4). Other compilers are not yet supported. Aborting build.")
endif()

# Target C++17
set(CMAKE_CXX_STANDARD 17)
# Disable extensions (turns gnu++17 to c++17)
set(CMAKE_CXX_EXTENSIONS OFF)

# Target 32-bit or 64-bit, based on ARCH variable.
if(ARCH EQUAL 32)
    message("Triggered 32-bit build (-m32).")
    add_definitions(-m32)
elseif(ARCH EQUAL 64)
    message("Triggered 64-bit build (-m64).")
    add_definitions(-m64)
# If 32-bit or 64-bit wasn't specified, just use the default.
elseif(NOT ARCH)
    message("Building for default architecture.")
else()
    message(FATAL_ERROR "Invalid architecture (${ARCH}) specified. Aborting build.")
endif()

# Our global compiler flags.
add_definitions(-Wall -Wextra -Werror -pedantic)

if(COMPILERTYPE STREQUAL "gcc")
    # -Wimplicit-fallthrough=0 is required for
    # GCC 7.x and onward. That is, until we switch
    # to C++17
    if(CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL "7" OR CMAKE_CXX_COMPILER_VERSION VERSION_GREATER "7")
        add_definitions(-Wimplicit-fallthrough=0)
    endif()
    # Set debug flags. -g is a default.
    #set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ")
    # Set release flags. -O3 is a default.
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s -fexpensive-optimizations")
elseif(COMPILERTYPE STREQUAL "clang")
    # Use libc++ if requested.
    if(LLVM)
        add_definitions(-stdlib=libc++)
        message("Using LLVM libc++...")
    endif()
    # Set debug flags. -g is a default.
    #set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ")
    # Set release flags. -O3 is a default.
    #set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ")
endif()

if(LD)
    message("Using ${LD} linker...")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=${LD}")
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../../lib/$<CONFIG>")

include_directories(include)

# CHANGEME: Include headers of dependencies.
include_directories(${CPGF_DIR}/include)

# CHANGEME: Include files to compile.
add_library(${TARGET_NAME} STATIC
    include/pawlib/avl_tree.hpp
    include/pawlib/base_flex_array.hpp
    include/pawlib/core_types.hpp
    include/pawlib/core_types_tests.hpp
    include/pawlib/flex_array.hpp
    include/pawlib/flex_array_tests.hpp
    include/pawlib/flex_bit_tests.hpp
    include/pawlib/flex_bit.hpp
    include/pawlib/flex_map.hpp
    include/pawlib/flex_queue.hpp
    include/pawlib/flex_queue_tests.hpp
    include/pawlib/flex_stack.hpp
    include/pawlib/flex_stack_tests.hpp
    include/pawlib/goldilocks.hpp
    include/pawlib/goldilocks_assertions.hpp
    include/pawlib/goldilocks_shell.hpp
    include/pawlib/iochannel.hpp
    include/pawlib/onechar.hpp
    include/pawlib/onechar_tests.hpp
    include/pawlib/onestring.hpp
    include/pawlib/onestring_tests.hpp
    include/pawlib/pawsort.hpp
    include/pawlib/pawsort_tests.hpp
    include/pawlib/pool.hpp
    include/pawlib/pool_tests.hpp
    include/pawlib/rigid_stack.hpp
    include/pawlib/singly_linked_list.hpp
    include/pawlib/stdutils.hpp

    src/core_types.cpp
    src/core_types_tests.cpp
    src/flex_array_tests.cpp
    src/flex_bit_tests.cpp
    src/flex_queue_tests.cpp
    src/flex_stack_tests.cpp
    src/goldilocks.cpp
    src/goldilocks_shell.cpp
    src/iochannel.cpp
    src/onechar.cpp
    src/onechar_tests.cpp
    src/onestring.cpp
    src/onestring_tests.cpp
    src/pawsort_tests.cpp
    src/pool_tests.cpp
    src/stdutils.cpp

)

# CHANGEME: Link against dependencies.
target_link_libraries(${TARGET_NAME} ${CPGF_DIR}/lib/libcpgf.a)

if(COMPILERTYPE STREQUAL "clang")
    if(SAN STREQUAL "address")
        add_definitions(-O1 -fsanitize=address -fno-optimize-sibling-calls -fno-omit-frame-pointer)
        set_property(TARGET ${TARGET_NAME} APPEND_STRING PROPERTY LINK_FLAGS " -fsanitize=address")
        message("Compiling with AddressSanitizer.")
    elseif(SAN STREQUAL "leak")
        add_definitions(-fsanitize=leak)
        set_property(TARGET ${TARGET_NAME} APPEND_STRING PROPERTY LINK_FLAGS " -fsanitize=leak")
        message("Compiling with LeakSanitizer.")
    elseif(SAN STREQUAL "memory")
        if(LLVM)
            add_definitions(-O1 -fsanitize=memory -fno-optimize-sibling-calls -fno-omit-frame-pointer -fsanitize-memory-track-origins)
            set_property(TARGET ${TARGET_NAME} APPEND_STRING PROPERTY LINK_FLAGS " -fsanitize=memory")
            message("Compiling with MemorySanitizer.")
        else()
            message("Skipping MemorySanitizer: requires libc++")
        endif()
    elseif(SAN STREQUAL "thread")
        add_definitions(-O1 -fsanitize=thread)
        set_property(TARGET ${TARGET_NAME} APPEND_STRING PROPERTY LINK_FLAGS " -fsanitize=thread")
        message("Compiling with ThreadSanitizer.")
    elseif(SAN STREQUAL "undefined")
        add_definitions(-fsanitize=undefined)
        set_property(TARGET ${TARGET_NAME} APPEND_STRING PROPERTY LINK_FLAGS " -fsanitize=undefined")
        message("Compiling with UndefiniedBehaviorSanitizer.")
    endif()
endif()
