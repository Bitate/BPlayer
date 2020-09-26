cmake_minimum_required(VERSION 3.8)

project(BPlayer)

enable_testing()

# By default, new Visual Studio projects link the C runtimes dynamically 
# but Google Test links them statically. This will generate an error 
# that looks something like the following: gtest.lib(gtest-all.obj) : 
# error LNK2038: mismatch detected for 'RuntimeLibrary': value 'MTd_StaticDebug' 
# doesn't match value 'MDd_DynamicDebug' in main.obj

# Force googletest to link dynamically
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(googletest)
add_subdirectory(src)
add_subdirectory(tests)
