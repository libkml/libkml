set(TESTS
attributes
color32
csv_splitter
date_time
expat_handler_ns
file
math_util
referent
string_util
tempfile
time_util
util
vec3
version
xml_element
xml_file
xml_namespaces
xmlns
net_cache
uri_parser
zip_file
expat_parser)

if(MINGW)
  #supress overflow warning for mingw
  set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/expat_parser_test.cc COMPILE_FLAGS "-Wno-overflow")
endif()

foreach(TEST ${TESTS})
  build_test(
    GROUP base
    NAME ${TEST}
    DEPENDS kmlbase)
endforeach()
