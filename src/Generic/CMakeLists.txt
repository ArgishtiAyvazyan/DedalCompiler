project (Generic)

# Header only library, therefore INTERFACE
add_library(Generic_lib INTERFACE)

# INTERFACE targets only have INTERFACE properties
target_include_directories(Generic_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(Generic_lib INTERFACE cxx_std_17)
