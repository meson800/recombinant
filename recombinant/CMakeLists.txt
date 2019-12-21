# CMakeList.txt : CMake project for recombinant, include source and define
# project specific logic here.
#
# Dependencies
find_package(Doxygen)
find_package(Python3 REQUIRED COMPONENTS Development)
find_package(wxWidgets REQUIRED COMPONENTS core base)

# We have to do library dirs here, because CMake 3.8 doesn't
# guarantee the target_link_directories command
if (wxWidgets_LIBRARY_DIRS)
    link_directories(recombinant PRIVATE ${wxWidgets_LIBRARY_DIRS})
endif()

# Add source to this project's executable.
set(RecombinantSources main.cpp)
if (WIN32)
	add_executable (recombinant WIN32 ${RecombinantSources})
else()
	add_executable(recombinant ${RecombinantSources})
endif()

# Ensure C++11 builds
set_property(TARGET recombinant PROPERTY CXX_STANDARD 11)


if (wxWidgets_INCLUDE_DIRS)
	target_include_directories(recombinant SYSTEM PRIVATE ${wxWidgets_INCLUDE_DIRS})
endif()

if (wxWidgets_DEFINITIONS)
	set_property(TARGET recombinant APPEND PROPERTY COMPILE_DEFINITIONS ${wxWidgets_DEFINITIONS})
endif()

if (wxWidgets_DEFINITIONS_DEBUG)
    set_property(TARGET recombinant APPEND PROPERTY COMPILE_DEFINITIONS_DEBUG ${wxWidgets_DEFINITIONS_DEBUG})
endif()

if (wxWidgets_CXX_FLAGS)
    # Flags are expected to be a string here, not a list.
    string(REPLACE ";" " " wxWidgets_CXX_FLAGS_str "${wxWidgets_CXX_FLAGS}")
	target_compile_options(recombinant PRIVATE ${wxWidgets_CXX_FLAGS_str})
    unset(wxWidgets_CXX_FLAGS_str)
endif()

# Link against Python dev libraries and wxwidgets
target_link_libraries(recombinant PRIVATE Python3::Python ${wxWidgets_LIBRARIES})

# Enable more warnings!
target_compile_options(recombinant PRIVATE
   $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
		-Wall -Werror>
   $<$<CXX_COMPILER_ID:MSVC>:
		/W4 /WX>)
# TODO: Add tests and install targets if needed.
