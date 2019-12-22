project (Generic)

# Header only library, therefore INTERFACE
add_library(Generic_lib STATIC Debug.cpp CException.cpp)

# INTERFACE targets only have INTERFACE properties
target_include_directories(Generic_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(Generic_lib INTERFACE cxx_std_17 )

target_link_libraries(Generic_lib PRIVATE -ldl -fpic -export-dynamic)

