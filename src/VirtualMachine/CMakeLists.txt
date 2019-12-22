project (VirtualMachine)

# Header only library, therefore INTERFACE
add_library(VirtualMachine_lib STATIC CFlags.cpp CProcessor.cpp CExecutor.cpp)

# INTERFACE targets only have INTERFACE properties
target_include_directories(VirtualMachine_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(VirtualMachine_lib INTERFACE cxx_std_17 )

target_link_libraries(VirtualMachine_lib PRIVATE -ldl -fpic -export-dynamic)
target_link_libraries(VirtualMachine_lib PRIVATE UserOutWriter_lib Generic_lib Parser_lib Compiler_lib Core_lib)
