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
  add_definitions(-DXML_UNICODE)
endif()

   # build_target(
   #   TEST
   #   GROUP base
   #   NAME attributes_test
   #   DEPENDS kmlbase
   #   )

   
#   add_executable(abc attributes_test.cc)
   
 #  target_link_libraries(abc ${GTEST_LIBRARY})
    

 foreach(TEST ${TESTS})
   build_target(
     TEST
     GROUP base
     NAME ${TEST}_test
     DEPENDS kmlbase
     )

 endforeach()
