macro(build_target)
  cmake_parse_arguments(LIB  "" "NAME" "SRCS;INCS;LINKS;DEPENDS" ${ARGN} )
  add_library(${LIB_NAME} ${LIB_SRCS})

  foreach(LIB_DEPEND ${LIB_DEPENDS})
    add_dependencies(${LIB_NAME} ${LIB_DEPEND})
    #well.. if the LIB_DEPEND is one of kml*
    #then we need to link it with target lib
    if(${LIB_DEPEND} MATCHES "^kml")
      list(APPEND LIB_LINKS ${LIB_DEPEND})
    endif()
  endforeach()
  target_link_libraries(${LIB_NAME} LINK_INTERFACE_LIBRARIES ${LIB_LINKS})
  
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
  add_executable(test_${TEST_NAME} ${TEST_NAME}_test.cc)
  add_dependencies(test_${TEST_NAME} ${TEST_DEPENDS})
  set(TEST_LINKS)
  foreach(TEST_D ${TEST_DEPENDS})
    get_target_property(VAR ${TEST_D} LINK_INTERFACE_LIBRARIES)
    list(APPEND TEST_LINKS ${VAR})
  endforeach()
  target_link_libraries(test_${TEST_NAME} ${TEST_DEPENDS} ${TEST_LINKS} ${GTEST_LIBRARY})
  add_test(${TEST_GROUP}_${TEST_NAME} ${CMAKE_BINARY_DIR}/bin/test_${TEST_NAME})
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
