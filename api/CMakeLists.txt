set (API_SOURCES GenbankFlatFile.cpp FastaFile.cpp FileFormat.cpp Sequence.cpp
  LocalFileSource.cpp Source.cpp)

add_library(recombinant_api_obj ${API_SOURCES})

add_executable(test_api tests.cpp $<TARGET_OBJECTS:recombinant_api_obj>)

# Use C++17 for API targets
set_property(TARGET recombinant_api_obj PROPERTY CXX11_STANDARD 17)
set_property(TARGET test_api PROPERTY CXX_STANDARD 17)
doctest_discover_tests(test_api)