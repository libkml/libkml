if(WIN32)
  cmake_minimum_required(VERSION 3.3)
else()
  cmake_minimum_required(VERSION 2.8)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
endif()

project(LibKML)

set(VERSION_MAJOR "1")
set(VERSION_MINOR "3")
set(VERSION_PATCH "1")
set(VERSION_STRING "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

option(BUILD_TESTING  "Build testing." OFF)
option(BUILD_EXAMPLES  "Build examples." OFF)
option(INSTALL_EXAMPLES   "Install examples sources and executables" OFF)
option(BUILD_SHARED_LIBS  "Build shared libs." ON)
option(WITH_SWIG   "Build all swig bindings"   OFF)
option(WITH_PYTHON "Build python bindings" OFF)
option(WITH_JAVA   "Build java bindings"   OFF)

set(CMAKE_INCLUDE_DIRECTORIES_BEFORE ON)

cmake_policy(SET CMP0026 OLD)
if(POLICY CMP0022)
  cmake_policy(SET CMP0022 NEW)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "CMAKE_BUILD_TYPE is not set. setting it to 'Release'")
  set(CMAKE_BUILD_TYPE Release)
endif()

if(NOT DEFINED BIN_INSTALL_DIR)
  set(BIN_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/bin")
endif(NOT DEFINED BIN_INSTALL_DIR)
if(NOT DEFINED LIB_INSTALL_DIR)
  set(LIB_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/lib")
endif(NOT DEFINED LIB_INSTALL_DIR)
if(NOT DEFINED DATA_INSTALL_DIR)
  set(DATA_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/share")
endif(NOT DEFINED DATA_INSTALL_DIR)
if(NOT DEFINED INCLUDE_INSTALL_DIR)
  set(INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/include/kml")
endif(NOT DEFINED INCLUDE_INSTALL_DIR)
if(NOT DEFINED MAN_INSTALL_DIR)
  set(MAN_INSTALL_DIR "${DATA_INSTALL_DIR}/man")
endif(NOT DEFINED MAN_INSTALL_DIR)
if(NOT DEFINED RESOURCE_INSTALL_DIR)
  set(RESOURCE_INSTALL_DIR "${DATA_INSTALL_DIR}/libkml${VERSION_MAJOR}/resource/")
endif(NOT DEFINED RESOURCE_INSTALL_DIR)
if(NOT DEFINED LOCALE_INSTALL_DIR)
  set(LOCALE_INSTALL_DIR "${DATA_INSTALL_DIR}/locale/")
endif(NOT DEFINED LOCALE_INSTALL_DIR)
if(NOT DEFINED JAVA_INSTALL_DIR)
  set(JAVA_INSTALL_DIR "${DATA_INSTALL_DIR}/java")
endif(NOT DEFINED JAVA_INSTALL_DIR)
if(NOT DEFINED JNI_INSTALL_DIR)
  set(JNI_INSTALL_DIR "${LIB_INSTALL_DIR}/jni")
endif(NOT DEFINED JNI_INSTALL_DIR)
if(NOT DEFINED PKGCONFIG_INSTALL_DIR)
  set(PKGCONFIG_INSTALL_DIR "${LIB_INSTALL_DIR}/pkgconfig")
endif(NOT DEFINED PKGCONFIG_INSTALL_DIR)


set(LIBKML_DATA_DIR  ${CMAKE_SOURCE_DIR}/testdata CACHE "Directory containing test data" PATH)

#AM_CXXFLAGS = -Wall -Wextra -Wno-unused-parameter -pedantic -fno-rtti
#AM_TEST_CXXFLAGS = -Wall -Wextra -Wno-unused-parameter -Werror -fno-rtti -DGTEST_HAS_RTTI=0

if(MSVC)
  set(LIBKML_CXX_FLAGS  "/DUNICODE /D_UNICODE")
  set(LIBKML_C_FLAGS    "/DUNICODE /D_UNICODE")
else()
  set(LIBKML_CXX_FLAGS  "-fPIC")
  set(LIBKML_C_FLAGS    "-fPIC")
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
  #-pedantic
  set(LIBKML_CXX_FLAGS "${LIBKML_CXX_FLAGS} -Wall -Wextra -Wno-unused-parameter -fno-rtti")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LIBKML_CXX_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${LIBKML_C_FLAGS}")

set(INSTALL_DIR "${CMAKE_INSTALL_PREFIX}" CACHE "install directory " PATH)

set(LIBKML_TARGETS)

include(LibKMLHelper)

add_subdirectory(third_party)

#TODO
#check if this is needed
if(NOT BUILD_SHARED_LIBS)    
  add_definitions(-DXML_STATIC) #for static expat    
endif()

add_subdirectory(src)

 if(BUILD_TESTING)
   enable_testing()
   add_subdirectory(tests)
 endif()

 if(BUILD_EXAMPLES)
   add_subdirectory(examples)
 endif()


if(UNIX)
  configure_file("${CMAKE_SOURCE_DIR}/cmake/libkml.pc.in"
    "${CMAKE_BINARY_DIR}/libkml.pc" @ONLY)
  install(FILES ${CMAKE_BINARY_DIR}/libkml.pc
    DESTINATION ${PKGCONFIG_INSTALL_DIR})
endif()
 
