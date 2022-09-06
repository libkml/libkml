find_package(GoogleTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/tests)
add_definitions("-DDATADIR=\"${LIBKML_DATA_DIR}\"")

if(NOT MSVC)
  add_link_options(-pthread)
endif()

add_subdirectory(kml)
if(WITH_SWIG)
  add_subdirectory(swig)
endif()
