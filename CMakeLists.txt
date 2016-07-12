cmake_minimum_required(VERSION 2.8)
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

if(POLICY CMP0022)
  cmake_policy(SET CMP0022 NEW)
endif()

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

if(WIN32 AND NOT CYGWIN AND NOT MINGW)
  set(DEF_INSTALL_CMAKE_DIR cmake)
else()
  set(DEF_INSTALL_CMAKE_DIR lib/cmake/libkml)
endif()
set(CMAKE_INSTALL_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH "Installation directory for CMake files")

set(CMAKE_MODULE_PATH
    ${CMAKE_SOURCE_DIR}/cmake
    ${CMAKE_MODULE_PATH})

set(LIBKML_DATA_DIR  ${CMAKE_SOURCE_DIR}/testdata CACHE "Directory containing test data" PATH)

#AM_CXXFLAGS = -Wall -Wextra -Wno-unused-parameter -pedantic -fno-rtti
#AM_TEST_CXXFLAGS = -Wall -Wextra -Wno-unused-parameter -Werror -fno-rtti -DGTEST_HAS_RTTI=0
if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unused-parameter -pedantic -fno-rtti")
  set(TEST_FLAGS "-Wall -Wextra -Wno-unused-parameter -fno-rtti -DGTEST_HAS_RTTI=0")
else()
  if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DUNICODE /D_UNICODE")
#    set(BUILD_SHARED_LIBS OFF)
  endif()
endif()

set(INSTALL_DIR "${CMAKE_INSTALL_PREFIX}" CACHE "install directory " PATH)
set(LIBKML_TARGETS)

include(LibKMLHelper)

include(SuperFind)

set(KMLBASE_DEPENDS)

find_package(Boost)
if(Boost_FOUND)
  message(STATUS "Found Boost: ${Boost_VERSION}")
else()
  include(External_boost)
  list(APPEND KMLBASE_DEPENDS BOOST)
  message(STATUS "Found Boost includes: ${Boost_INCLUDE_DIRS}")
endif()

include_directories(${Boost_INCLUDE_DIRS})

if(NOT BUILD_SHARED_LIBS)    
    add_definitions(-DXML_STATIC) #for static expat    
endif()

#expat is dependency for kmlbase and kmldom
super_find_package(EXPAT)
include_directories(${EXPAT_INCLUDE_DIRS})

super_find_package(ZLIB)
include_directories(${ZLIB_INCLUDE_DIR})

super_find_package(MiniZip)
include_directories(${MINIZIP_INCLUDE_DIR})

super_find_package(UriParser)
include_directories(${URIPARSER_INCLUDE_DIR})

include_directories(${CMAKE_SOURCE_DIR}/src)

add_dependencies_if_needed(KMLBASE ZLIB)
add_dependencies_if_needed(KMLBASE MiniZip)
add_dependencies_if_needed(KMLBASE UriParser)
add_dependencies_if_needed(KMLBASE EXPAT)

add_subdirectory(src)

if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()

if(BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "")
set(CONFIG_TYPE "NOCONFIG")
else()
  string(TOUPPER ${CMAKE_BUILD_TYPE} CONFIG_TYPE)
endif()

if(NOT WIN32 OR MINGW)
  configure_file("${CMAKE_SOURCE_DIR}/cmake/libkml.pc.in"
    "${CMAKE_BINARY_DIR}/libkml.pc" @ONLY)
  install(FILES ${CMAKE_BINARY_DIR}/libkml.pc
    DESTINATION ${PKGCONFIG_INSTALL_DIR})
endif()
 
# Make relative paths absolute (needed later on)
foreach(p LIB BIN INCLUDE CMAKE)
  set(var ${p}_INSTALL_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()

export(TARGETS ${LIBKML_TARGETS}
  FILE "${CMAKE_BINARY_DIR}/LibKMLTargets.cmake")
  
# Create the LibKMLConfig.cmake and LibKMLConfigVersion files
file(RELATIVE_PATH REL_INCLUDE_DIR "${CMAKE_INSTALL_DIR}"
  "${INCLUDE_INSTALL_DIR}")

# ... for the build tree
set(CONF_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/src")
configure_file(cmake/LibKMLConfig.cmake.in
  "${PROJECT_BINARY_DIR}/LibKMLConfig.cmake" @ONLY)

# ... for the install tree
set(CONF_INCLUDE_DIRS "\${LIBKML_CMAKE_DIR}/${REL_INCLUDE_DIR}")
configure_file(cmake/LibKMLConfig.cmake.in
  "${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/LibKMLConfig.cmake" @ONLY)

# ... for both
configure_file(cmake/LibKMLConfigVersion.cmake.in
  "${CMAKE_BINARY_DIR}/LibKMLConfigVersion.cmake" @ONLY)
 
# Install the LibKMLConfig.cmake and LibKMLConfigVersion.cmake
install(FILES
  "${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/LibKMLConfig.cmake"
  "${CMAKE_BINARY_DIR}/LibKMLConfigVersion.cmake"
  DESTINATION ${DEF_INSTALL_CMAKE_DIR} )

# Install the export set for use with the install-tree
install(EXPORT LibKMLTargets DESTINATION ${DEF_INSTALL_CMAKE_DIR})
