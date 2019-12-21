# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)
set (CMAKE_USER_MAKE_RULES_OVERRIDE "${CMAKE_CURRENT_LIST_DIR}/CompilerOptions.cmake")
string (REGEX REPLACE "/W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")



project ("recombinant")

# Include sub-projects.
add_subdirectory ("recombinant")
