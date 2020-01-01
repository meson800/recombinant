set (API_SOURCES GenbankFlatFile.cpp FastaFile.cpp FileFormat.cpp)

add_library(recombinant_api_obj OBJECT ${API_SOURCES})
set_property(TARGET recombinant_api_obj PROPERTY CXX_STANDARD 11)

add_executable(test_api tests.cpp $<TARGET_OBJECTS:recombinant_api_obj>)
set_property(TARGET test_api PROPERTY CXX_STANDARD 11)
doctest_discover_tests(test_api)