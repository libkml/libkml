file(GLOB SRCS "*.cc"
  contrib/minizip/unzip.c
  contrib/minizip/iomem_simple.c)

if(WIN32)
  list(APPEND SRCS contrib/strptime.c)
  list(REMOVE_ITEM SRCS "${CMAKE_CURRENT_SOURCE_DIR}/file_posix.cc")
  if(MINGW)
      #use unicode functions from the windows api
      add_definitions(-DUNICODE -D_UNICODE)
      #supress long-long warning for mingw
      set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/time_util.cc COMPILE_FLAGS "-Wno-long-long")
  endif()
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
  LINKS ${ZLIB_LIBRARY} ${MINIZIP_LIBRARIES} ${URIPARSER_LIBRARY} ${EXPAT_LIBRARY} )
