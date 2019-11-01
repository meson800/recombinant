if (MSVC)
    # remove default warning level from CMAKE_CXX_FLAGS_INIT on MSVC
    string (REGEX REPLACE "/W[0-4]" "" CMAKE_CXX_FLAGS_INIT "${CMAKE_CXX_FLAGS_INIT}")
endif()