project (UserOutWriter)

# Header only library, therefore INTERFACE
add_library(UserOutWriter_lib STATIC UIO.cpp)

# INTERFACE targets only have INTERFACE properties
target_include_directories(UserOutWriter_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(UserOutWriter_lib PRIVATE Generic_lib)

target_compile_features(UserOutWriter_lib INTERFACE cxx_std_17)
