# CMakeList.txt : CMake project for recombinant, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
if (WIN32)
	add_executable (recombinant WIN32 "main.cpp")
endif()

# Ensure C++11 builds
set_property(TARGET recombinant PROPERTY CXX_STANDARD 11)

# Dependencies
find_package(Doxygen)
find_package(Python3 REQUIRED COMPONENTS Development)
find_package(wxWidgets REQUIRED COMPONENTS core base)

# Link against Python dev libraries and wxwidgets
include(${wxWidgets_USE_FILE})
target_link_libraries(recombinant PRIVATE Python3::Python ${wxWidgets_LIBRARIES})

# TODO: Add tests and install targets if needed.
