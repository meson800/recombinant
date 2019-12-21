# CMakeList.txt : CMake project for recombinant, include source and define
# project specific logic here.
#
# Dependencies
if (WIN32)
  string(REGEX REPLACE ".$" "x" MSVC_TOOLSET_VERSION ${MSVC_TOOLSET_VERSION})
  message(STATUS "Toolset path for wxWidgets: ${MSVC_TOOLSET_VERSION}")
endif()

# Setup git revision information
include(GetGitRevisionDescription)

# Extract version information from Git
git_describe(VERSION)
git_get_exact_tag(VERSION_EXACT)
git_local_changes(VERSION_IS_DIRTY)
string(REGEX REPLACE "^v([0-9]+)\\..*" "\\1" VERSION_MAJOR "${VERSION}")
string(REGEX REPLACE "^v[0-9]+\\.([0-9]+).*" "\\1" VERSION_MINOR "${VERSION}")
string(REGEX REPLACE "^v[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" VERSION_PATCH "${VERSION}")
string(REGEX REPLACE "^v[0-9]+\\.[0-9]+\\.[0-9]+(.*)" "\\1" VERSION_SHA1 "${VERSION}")
set(VERSION_SHORT "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

if (git_get_exact_tag)
  set(VERSION_STRING "${VERSION_EXACT}")
else()
  if (VERSION_IS_DIRTY MATCHES "DIRTY")
    set(VERSION_STRING "${VERSION}-dirty")
  else()
    set(VERSION_STRING "${VERSION}")
  endif()
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/version.cpp.in ${CMAKE_CURRENT_BINARY_DIR}/version.cpp)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/version.h ${CMAKE_CURRENT_BINARY_DIR}/version.h)
set(VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/version.cpp")

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
	add_executable (recombinant WIN32 ${RecombinantSources} ${VERSION_FILE})
else()
	add_executable(recombinant ${RecombinantSources} ${VERSION_FILE})
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
