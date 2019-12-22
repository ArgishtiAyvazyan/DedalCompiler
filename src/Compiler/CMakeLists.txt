project (Compiler)

# Header only library, therefore INTERFACE
add_library(Compiler_lib STATIC Commands.cpp CCompiler.cpp)

# INTERFACE targets only have INTERFACE properties
target_include_directories(Compiler_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(Compiler_lib INTERFACE cxx_std_17 )

target_link_libraries(Compiler_lib PRIVATE -ldl -fpic -export-dynamic)
target_link_libraries(Compiler_lib PRIVATE UserOutWriter_lib Generic_lib Parser_lib Core_lib)
