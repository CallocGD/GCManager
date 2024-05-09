cmake_minimum_required(VERSION 3.6)

# Used a python script to help me : https://github.com/astavonin/gen-cmake


if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
    message( FATAL_ERROR "In-source builds not allowed. Please make a new directory and run CMake from there. You may need to remove CMakeCache.txt." )
endif()

set(PROJECT_NAME gcmanager)
project(${PROJECT_NAME})

SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/bin
        CACHE PATH
        "Single Directory for all"
    )

SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/bin
        CACHE PATH
        "Single Directory for all"
    )

SET (CMAKE_ARCHIVE_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/lib
        CACHE PATH
        "Single Directory for all"
    )





# TODO: uncomment if have unit tests
# enable_testing()

find_program( CLANG_TIDY NAMES clang-tidy)
# NOTE: you can add search paths for example `PATHS /usr/local/opt/llvm/bin/`

message("\n--------------------------------\n")
message("PROJECT NAME:\t\t${PROJECT_NAME}")
message("CMAKE_SYSTEM_NAME:\t${CMAKE_SYSTEM_NAME}")
message("CMAKE_C_COMPILER:\t${CMAKE_C_COMPILER}")
message("CMAKE_CXX_COMPILER:\t${CMAKE_CXX_COMPILER}")
message("CMAKE_GENERATOR:\t${CMAKE_GENERATOR}")
message("CMAKE_BUILD_TYPE:\t${CMAKE_BUILD_TYPE}")
message("CMAKE_BINARY_DIR:\t${CMAKE_BINARY_DIR}")
message("CMAKE_MODULE_PATH:\t${CMAKE_MODULE_PATH}")
message("CMAKE_PREFIX_PATH:\t${CMAKE_PREFIX_PATH}")
message("clang-tidy:\t\t${CLANG_TIDY}")
message("\n--------------------------------\n")


set(gcmanager_sources
    mimalloc/src/alloc.c
    mimalloc/src/alloc-aligned.c
    mimalloc/src/alloc-posix.c
    mimalloc/src/arena.c
    mimalloc/src/bitmap.c
    mimalloc/src/heap.c
    mimalloc/src/init.c
    mimalloc/src/libc.c
    mimalloc/src/options.c
    mimalloc/src/os.c
    mimalloc/src/page.c
    mimalloc/src/random.c
    mimalloc/src/segment.c
    mimalloc/src/segment-map.c
    mimalloc/src/stats.c
    mimalloc/src/prim/prim.c
    src/GCManager.cpp
    gc/gc.c
    gc/log.c
)



add_library(${PROJECT_NAME}-static STATIC ${${PROJECT_NAME}_sources})

target_include_directories(gcmanager-static PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/mimalloc/include
    ${CMAKE_CURRENT_SOURCE_DIR}/gc
)


# NOTE: this will slow down compilation, but you'll have static code analysis :)
if(CLANG_TIDY)
    set_property(
        TARGET ${PROJECT_NAME}
        PROPERTY CXX_CLANG_TIDY "${CLANG_TIDY}")
endif()




