
super_find_package(MiniZip)
include_directories(${MINIZIP_INCLUDE_DIR})

super_find_package(ZLIB)
include_directories(${ZLIB_INCLUDE_DIR})

super_find_package(UriParser)
include_directories(${URIPARSER_INCLUDE_DIR})

# super_find_package(EXPAT)

find_package(Boost)
if(Boost_FOUND)
  message(STATUS "Found Boost: ${Boost_VERSION}")
else()
  include(External_boost)
  list(APPEND KMLBASE_DEPENDS BOOST)
  message(STATUS "Found Boost includes: ${Boost_INCLUDE_DIRS}")
endif()

include_directories(${Boost_INCLUDE_DIRS})

file(GLOB SRCS "*.cc"
  contrib/minizip/unzip.c
  contrib/minizip/iomem_simple.c)

if(WIN32)
  list(REMOVE_ITEM SRCS "${CMAKE_CURRENT_SOURCE_DIR}/file_posix.cc")
else()
  list(REMOVE_ITEM SRCS "${CMAKE_CURRENT_SOURCE_DIR}/file_win32.cc")
  #supress long-long warning for linux
  set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/zip_file.cc COMPILE_FLAGS "-Wno-long-long")
endif()

set(INCS
  attributes.h
  csv_splitter.h
  date_time.h
  color32.h
  expat_handler.h
  expat_handler_ns.h
  expat_parser.h
  file.h
  math_util.h
  memory_file.h
  mimetypes.h
  net_cache.h
  referent.h
  string_util.h
  tempfile.h
  time_util.h
  util.h
  vec3.h
  version.h
  xml_element.h
  xml_file.h
  xml_namespaces.h
  xmlns.h
  zip_file.h)

set(KMLBASE_DEPENDS)
if(EXISTS ZLIB)
list(APPEND KMLBASE_DEPENDS ZLIB)
endif()

if(EXISTS MiniZip)
list(APPEND KMLBASE_DEPENDS MiniZip)
endif()

if(EXISTS UriParser)
list(APPEND KMLBASE_DEPENDS UriParser)
endif()

build_target(
  NAME kmlbase
  SRCS ${SRCS}
  INCS ${INCS}
  DEPENDS ${KMLBASE_DEPENDS}
  LINKS ${ZLIB_LIBRARIES} ${MINIZIP_LIBRARIES} ${EXPAT_LIBRARY} )
