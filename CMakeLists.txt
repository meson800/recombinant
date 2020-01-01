# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules ${CMAKE_MODULE_PATH})

# Read in license and authors file
file(READ AUTHORS AUTHORS_STRING)

project ("recombinant")

enable_testing()

# Include sub-projects.
add_subdirectory("api")
add_subdirectory("recombinant")
