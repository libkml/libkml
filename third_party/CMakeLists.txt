####################################### BOOST #######################################
find_package(Boost)
if(Boost_FOUND)
  message(STATUS "Found BOOST: ${Boost_INCLUDE_DIR} (${Boost_VERSION})")
else()
  message(STATUS "BOOST not found. We will use third_party/BOOST (ExternalProject)")  
  include(ExternalProject)
  ExternalProject_Add(BOOST
    PREFIX BOOST
    URL "https://downloads.sourceforge.net/project/boost/boost/1.63.0/boost_1_63_0.tar.gz"
    URL_MD5 7b493c08bc9557bbde7e29091f28b605
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    )
  
  set(Boost_INCLUDE_DIR "${CMAKE_BINARY_DIR}/third_party/BOOST/src/BOOST")
  message(STATUS "Boost_INCLUDE_DIR = ${Boost_INCLUDE_DIR}")
endif()

####################################### EXAPT #######################################
find_package(EXPAT)
add_library(EXPAT SHARED IMPORTED GLOBAL)
if(NOT EXPAT_FOUND)
  message(STATUS "EXPAT not found. We will use third_party/expat")
  add_subdirectory(expat)
  add_dependencies(EXPAT expat)
  get_property(EXPAT_LIBRARY TARGET expat PROPERTY LOCATION)
  set(EXPAT_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/expat" )  
endif()
set_property(TARGET EXPAT PROPERTY IMPORTED_LOCATION ${EXPAT_LIBRARY} )
set_property(TARGET EXPAT PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${EXPAT_INCLUDE_DIRS} )

####################################### ZLIB #######################################
add_library(ZLIB SHARED IMPORTED GLOBAL)
find_package(ZLIB)
if(NOT ZLIB_FOUND)
  message(STATUS "ZLIB not found. We will use third_party/zlib")
  add_subdirectory(zlib)
  add_dependencies(ZLIB zlib)
  get_property(ZLIB_LIBRARY TARGET zlib PROPERTY LOCATION)
  set(ZLIB_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/zlib;${CMAKE_CURRENT_BINARY_DIR}/zlib" )  
endif()
set_property(TARGET ZLIB PROPERTY IMPORTED_LOCATION ${ZLIB_LIBRARY} )
set_property(TARGET ZLIB PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${ZLIB_INCLUDE_DIR} )

####################################### URIPARSER #######################################
find_package(URIPARSER QUIET)
if(URIPARSER_FOUND)
  add_library(URIPARSER SHARED IMPORTED GLOBAL)
  set_property(TARGET URIPARSER PROPERTY IMPORTED_LOCATION ${URIPARSER_LIBRARY} )
  set_property(TARGET URIPARSER PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${URIPARSER_INCLUDE_DIR} )
else()  
  message(STATUS "URIPARSER not found. We will use third_party/uriparser")
  file(GLOB URIPARSER_SOURCES uriparser/src/*.c)
  add_library(URIPARSER OBJECT ${URIPARSER_SOURCES})
  target_include_directories(URIPARSER PUBLIC uriparser/include )
endif()

####################################### MINIZIP #######################################
find_package(MINIZIP QUIET)
if(MINIZIP_FOUND)
  add_library(MINIZIP SHARED IMPORTED GLOBAL)
  set_property(TARGET MINIZIP PROPERTY IMPORTED_LOCATION ${MINIZIP_LIBRARY} )
  set_property(TARGET MINIZIP PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${MINIZIP_INCLUDE_DIR} )
else()  
  message(STATUS "MINIZIP not found. We will use third_party/zlib/contrib/minizip")  
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
add_dependencies(MINIZIP ZLIB)

