cmake_minimum_required(VERSION 3.6)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# The project name
project(AssemblyCompiler)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(
        -g
        -Wall
        # -Wextra
        -pedantic
        -Werror
        -Wfloat-equal
        -Wshadow
        -Wpointer-arith
        -ftrapv
        -fverbose-asm
        -finstrument-functions
        -Wcast-align
        -Wstrict-overflow=5
        -Wwrite-strings
        -Wcast-qual
        # -Wswitch-default
        -Wswitch-enum
        # -Wconversion
        -Wunreachable-code
        # -save-temps
        # -Weffc++
    )
endif()

add_subdirectory(Generic)
add_subdirectory(UserOutWriter)
add_subdirectory(Parser)
add_subdirectory(Application)
add_subdirectory(VirtualMachine)
