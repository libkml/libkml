
super_find_package(MiniZip)
include_directories(${MINIZIP_INCLUDE_DIR})

super_find_package(ZLIB)
include_directories(${ZLIB_INCLUDE_DIR})

super_find_package(EXPAT)
include_directories(${EXPAT_INCLUDE_DIR})



##set(LIBKML_TARGETS)
# set(KMLBASE_LINK_LIBS "" CACHE INTERNAL "KMLBASE_LINK_LIBS")
# set(KMLBASE_DEPENDS "" CACHE INTERNAL "KMLBASE_DEPENDS")
# set(MINIZIP_DEPENDS "" CACHE INTERNAL "MINIZIP_DEPENDS")

find_package(Boost)
if(Boost_FOUND)
  message(STATUS "Found Boost: ${Boost_VERSION}")
else()
  include(External_boost)
  list(APPEND KMLBASE_DEPENDS BOOST)
  message(STATUS "Found Boost includes: ${Boost_INCLUDE_DIRS}")
endif()

include_directories(${Boost_INCLUDE_DIRS})

# list(APPEND KMLBASE_LINK_LIBS ${EXPAT_LIBRARY})
# list(APPEND KMLBASE_LINK_LIBS ${ZLIB_LIBRARIES})
# list(APPEND KMLBASE_LINK_LIBS ${MINIZIP_LIBRARIES})
# list(APPEND KMLBASE_LINK_LIBS ${URIPARSER_LIBRARY})

# find_package(UriParser)
# if(URIPARSER_FOUND)
#   include_directories(${URIPARSER_INCLUDE_DIR})
# else()
#   include(External_uriparser)
#   list(APPEND KMLBASE_DEPENDS URIPARSER)
# endif()

#configure_project(UriParser)

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

build_target(
  NAME kmlbase
  SRCS ${SRCS}
  INCS ${INCS}
  DEPENDS ${KMLBASE_DEPENDS}
  LINKS ${ZLIB_LIBRARIES} ${MINIZIP_LIBRARIES} ${EXPAT_LIBRARY} )
