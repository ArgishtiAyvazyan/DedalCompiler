project (Core)

# Header only library, therefore INTERFACE
add_library(Core_lib STATIC CInsArg.cpp)

# INTERFACE targets only have INTERFACE properties
target_include_directories(Core_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(Core_lib INTERFACE cxx_std_17 )

target_link_libraries(Core_lib PRIVATE -ldl -fpic -export-dynamic)

