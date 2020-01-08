# CMakeList.txt : CMake project for recombinant, include source and define
# project specific logic here.
#
# Dependencies

# Locate the runtime DLLs we need
if (WIN32)
  set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP)
  include(InstallRequiredSystemLibraries)
endif()

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

# On Mac, find the Python framework so we can embed it
set(Python_FIND_FRAMEWORK FIRST)
find_package(Python3 REQUIRED COMPONENTS Development)
find_package(wxWidgets REQUIRED COMPONENTS core base aui)

include(${wxWidgets_USE_FILE})

# Add source to this project's executable.
set(RecombinantSources main.cpp AboutDialog.cpp MainFrame.cpp
  TreeWindow.cpp ViewWindow.cpp strings.cpp)
if (WIN32)
	add_executable (recombinant WIN32 ${RecombinantSources} ${VERSION_FILE} icons/main.rc)
elseif(APPLE)
	set(ICON_FILE ${CMAKE_CURRENT_SOURCE_DIR}/icons/main.icns)
	set_source_files_properties(${ICON_FILE} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
	add_executable(recombinant MACOSX_BUNDLE ${RecombinantSources} ${VERSION_FILE} ${ICON_FILE})
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Info.plist.in ${CMAKE_CURRENT_BINARY_DIR}/Info.plist)
	set_target_properties(recombinant PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_BINARY_DIR}/Info.plist)
	set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/BundleMacOS.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/BundleMacOS.cmake @ONLY)
	install(SCRIPT ${CMAKE_CURRENT_BINARY_DIR}/BundleMacOS.cmake COMPONENT Runtime)
else()
	add_executable (recombinant ${RecombinantSources} ${VERSION_FILE})
endif()

# If on windows, copy DLLs into output directory
if (WIN32)
  set(wxp "C:\\wxWidgets\\lib\\vc14x_x64_dll\\")
  if (CMAKE_BUILD_TYPE MATCHES Debug)
    set(debug_files 
      "${wxp}wxbase313ud_vc14x_x64.dll"
      "${wxp}wxbase313ud_vc14x_x64.pdb"
      "${wxp}wxmsw313ud_aui_vc14x_x64.dll"
      "${wxp}wxmsw313ud_aui_vc14x_x64.pdb"
      "${wxp}wxmsw313ud_core_vc14x_x64.dll"
      "${wxp}wxmsw313ud_core_vc14x_x64.pdb")
    add_custom_command(TARGET recombinant POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${debug_files} $<TARGET_FILE_DIR:recombinant>)
  else()
    set(release_files 
      "${wxp}wxbase313u_vc14x_x64.dll"
      "${wxp}wxmsw313u_aui_vc14x_x64.dll"
      "${wxp}wxmsw313u_core_vc14x_x64.dll")
    add_custom_command(TARGET recombinant POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${release_files} $<TARGET_FILE_DIR:recombinant>)
    # And copy over runtime into a specific folder for release builds
    add_custom_command(TARGET recombinant POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
      ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS} $<TARGET_FILE_DIR:recombinant>)
  endif()
endif()

# Ensure C++11 builds
set_property(TARGET recombinant PROPERTY CXX_STANDARD 11)

# Link against Python dev libraries and wxwidgets
target_link_libraries(recombinant PRIVATE Python3::Python ${wxWidgets_LIBRARIES})
message(STATUS "Loaded wx libraries: ${wxWidgets_LIBRARIES}")

# Enable more warnings!
target_compile_options(recombinant PRIVATE
   $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
		-Wall -Werror>
   $<$<CXX_COMPILER_ID:MSVC>:
		/W4 /WX>)

if (WIN32)
    string (REGEX REPLACE "/W3" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()
