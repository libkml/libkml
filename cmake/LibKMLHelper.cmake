macro(build_target)
  cmake_parse_arguments(LIB  "" "NAME" "SRCS;INCS;LINKS;DEPENDS" ${ARGN} )
  add_library(${LIB_NAME} ${LIB_SRCS})

  set(INTERFACE_LINKS)
  set(PUBLIC_LINKS)
  foreach(LIB_DEPEND ${LIB_DEPENDS})
    if(${LIB_DEPEND} MATCHES "^kml")
      list(APPEND INTERFACE_LINKS ${LIB_DEPEND})
    endif()
    add_dependencies(${LIB_NAME} ${LIB_DEPEND})
  endforeach()
  
  foreach(LIB_LINK ${LIB_LINKS})
    if(NOT ${LIB_LINK} MATCHES "^kml")
      list(APPEND PUBLIC_LINKS ${LIB_LINK})
    endif()
  endforeach()
  target_link_libraries(${LIB_NAME} ${PUBLIC_LINKS})
  if(INTERFACE_LINKS)
    if(MINGW OR APPLE)
      target_link_libraries(${LIB_NAME} ${INTERFACE_LINKS})
    else()
      target_link_libraries(${LIB_NAME} LINK_INTERFACE_LIBRARIES ${INTERFACE_LINKS})
    endif()
  endif()
  if(VERSION_STRING)
    set_target_properties(${LIB_NAME} PROPERTIES
      VERSION   "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}"
      SOVERSION "${VERSION_MAJOR}")
  endif()
  string(LENGTH ${LIB_NAME} ${LIB_NAME}_LEN)
  MATH(EXPR ${LIB_NAME}_END "${${LIB_NAME}_LEN} - 3")
  string(SUBSTRING ${LIB_NAME} 3 ${${LIB_NAME}_END} ${LIB_NAME}_INCLUDE_DIR)
  install(
    FILES ${LIB_INCS}
    DESTINATION ${INCLUDE_INSTALL_DIR}/${${LIB_NAME}_INCLUDE_DIR})

  install_target(${LIB_NAME})

endmacro(build_target)

macro(install_target _target)
  install(TARGETS ${_target}
    EXPORT LibKMLTargets
    RUNTIME DESTINATION ${BIN_INSTALL_DIR}
    LIBRARY DESTINATION ${LIB_INSTALL_DIR}
    ARCHIVE DESTINATION ${LIB_INSTALL_DIR})
  
  list(LENGTH LIBKML_TARGETS LIBKML_TARGETS_LENGTH)
  if(LIBKML_TARGETS_LENGTH LESS 1)
    set(LIBKML_TARGETS "${_target}" PARENT_SCOPE)
  else()
    set(LIBKML_TARGETS "${LIBKML_TARGETS};${_target}" PARENT_SCOPE)
    endif()
endmacro(install_target)

function(build_test)
  cmake_parse_arguments(TEST  "" "GROUP;NAME" "DEPENDS" ${ARGN} )
  add_executable(${TEST_GROUP}_${TEST_NAME}_test ${TEST_NAME}_test.cc)
  add_dependencies(${TEST_GROUP}_${TEST_NAME}_test ${TEST_DEPENDS})
  set(TEST_LINKS)
  foreach(TEST_D ${TEST_DEPENDS})
    get_target_property(LINK_PROP ${TEST_D} LINK_INTERFACE_LIBRARIES)
    if(LINK_PROP)
      list(APPEND TEST_LINKS ${LINK_PROP})
    endif()
  endforeach()
  target_link_libraries(${TEST_GROUP}_${TEST_NAME}_test ${TEST_LINKS} ${TEST_DEPENDS} ${GTEST_LIBRARY})
  add_test(${TEST_GROUP}_${TEST_NAME} ${CMAKE_BINARY_DIR}/bin/${TEST_GROUP}_${TEST_NAME}_test)
endfunction(build_test)

function(build_example)
  cmake_parse_arguments(EXAMPLE  "" "NAME" "LINKS;DEPENDS" ${ARGN} )
  add_executable(example_${EXAMPLE_NAME} ${EXAMPLE_NAME}.cc)
  add_dependencies(example_${EXAMPLE_NAME} ${EXAMPLE_DEPENDS})
  target_link_libraries(example_${EXAMPLE_NAME} ${EXAMPLE_LINKS} ${EXAMPLE_DEPENDS})
endfunction(build_example)


macro(include_project_vars _project _lib)
  set(${_project}_INCLUDE_DIR "${INSTALL_DIR}/include")
  if(WIN32)
    set(_suffix ${CMAKE_LINK_LIBRARY_SUFFIX})
  else(UNIX)
    if(BUILD_SHARED_LIBS)
      set(_suffix ${CMAKE_SHARED_LIBRARY_SUFFIX})
    else()
      set(_suffix ".a")
    endif()
  endif(WIN32)
  set(${_project}_LIBRARY "${INSTALL_DIR}/lib/${_lib}${_suffix}")
  include_directories(${${_project}_INCLUDE_DIR})
endmacro()
