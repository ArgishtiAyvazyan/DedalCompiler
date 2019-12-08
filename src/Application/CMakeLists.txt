project(Application)

# All sources that also need to be tested in unit tests go into a static library
# add_library(Aplication_lib STATIC GMain.h)
# target_include_directories(Aplication_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# The main program
add_executable(gmain_exec main.cpp)
target_link_libraries(gmain_exec PRIVATE Generic_lib UserOutWriter_lib Parser_lib)
target_compile_definitions(gmain_exec PRIVATE CATCH_CONFIG_CONSOLE_WIDTH=60)

