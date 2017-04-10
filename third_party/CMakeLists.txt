find_package(Boost REQUIRED)
if(Boost_FOUND)
  message(STATUS "Found Boost: ${Boost_VERSION}")
  #set(BOOST_INCLUDE_DIRS "${Boost_INCLUDE_DIR}" CACHE INTERNAL "")
else()
  message(FATAL_ERROR "Boost not found. We will use third_party/boost")
  #set(BOOST_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/boost CACHE INTERNAL "")
endif()

find_package(EXPAT)

if(EXPAT_FOUND)
  add_library(EXPAT SHARED IMPORTED GLOBAL)
  set_property(TARGET EXPAT PROPERTY IMPORTED_LOCATION ${EXPAT_LIBRARY} )
  set_property(TARGET EXPAT PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${EXPAT_INCLUDE_DIRS} )
else()
   message(STATUS "Expat not found. We will use third_party/expat")
  # add_subdirectory(expat)
  # set(LIBKML_EXPAT_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/expat/lib CACHE INTERNAL "")
  # set(LIBKML_EXPAT_LIBRARY ${CMAKE_BINARY_DIR}/lib/expat.lib CACHE INTERNAL "")
endif()

find_package(ZLIB)
if(ZLIB_FOUND)
  add_library(ZLIB SHARED IMPORTED GLOBAL)
  set_property(TARGET ZLIB PROPERTY IMPORTED_LOCATION ${ZLIB_LIBRARY} )
  set_property(TARGET ZLIB PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${ZLIB_INCLUDE_DIR} )
else()
   message(STATUS "zlib not found.  We will use third_party/zlib")
  # add_subdirectory(zlib)
  # set(LIBKML_ZLIB_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/zlib/contrib/;${CMAKE_CURRENT_SOURCE_DIR}/zlib;${CMAKE_CURRENT_BINARY_DIR}/zlib" CACHE INTERNAL "")
  # list(APPEND LIBKML_ZLIB_INCLUDE_DIRS )
  # set(LIBKML_ZLIB_LIBRARY ${CMAKE_BINARY_DIR}/lib/zlibd.lib CACHE INTERNAL "")
endif()

find_package(URIPARSER QUIET)
if(URIPARSER_FOUND)
  add_library(URIPARSER SHARED IMPORTED GLOBAL)
  set_property(TARGET URIPARSER PROPERTY IMPORTED_LOCATION ${URIPARSER_LIBRARY} )
  set_property(TARGET URIPARSER PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${URIPARSER_INCLUDE_DIR} )

else()  
  message(STATUS "UriParser not found. We will use third_party/uriparser")
  file(GLOB URIPARSER_SOURCES uriparser/src/*.c)

  add_library(URIPARSER OBJECT ${URIPARSER_SOURCES})
  target_include_directories(URIPARSER PUBLIC uriparser/include )

  #target_compile_definitions(MINIZIP PUBLIC "-DNOCRYPT")
  #set_property(TARGET URIPARSER PROPERTY IMPORTED_LOCATION "${CMAKE_CURRENT_BINARY_DIR}/uriparser.so" )
  #set_property(TARGET URIPARSER PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${URIPARSER_INCLUDE_DIRS} )  

endif()


find_package(MINIZIP QUIET)
if(MINIZIP_FOUND)
  add_library(MINIZIP SHARED IMPORTED GLOBAL)
  set_property(TARGET MINIZIP PROPERTY IMPORTED_LOCATION ${MINIZIP_LIBRARY} )
  set_property(TARGET MINIZIP PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${MINIZIP_INCLUDE_DIR} )
else()  
  message(STATUS "minizip not found. We will use third_party/zlib/contrib/minizip")  
  set(LIBKML_MINIZIP_SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/zlib/contrib/minizip/unzip.c
    ${CMAKE_CURRENT_SOURCE_DIR}/zlib/contrib/minizip/zip.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/zlib/contrib/minizip/mztools.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/zlib/contrib/minizip/ioapi.c 
    )

  if(WIN32)
    set(LIBKML_MINIZIP_SOURCES
      ${LIBKML_MINIZIP_SOURCES}
      ${CMAKE_CURRENT_SOURCE_DIR}/zlib/contrib/minizip/iowin32.c
      )
  endif()
  

  add_library(MINIZIP OBJECT ${LIBKML_MINIZIP_SOURCES})
  target_include_directories(MINIZIP PUBLIC ${ZLIB_INCLUDE_DIR} )
  target_include_directories(MINIZIP PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/zlib/contrib )
  #add a test to check this 
  target_compile_definitions(MINIZIP PUBLIC "-DNOCRYPT")

endif()


