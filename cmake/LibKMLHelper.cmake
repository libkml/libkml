#TODO; s/INCS/HDRS/g
function(build_target)
  cmake_parse_arguments(LIB  "TEST" "NAME;GROUP" "SRCS;INCS;INCLUDES;LINKS;DEPENDS" ${ARGN} )

  if(LIB_TEST)    
    if(NOT LIB_SRCS)
      set(LIB_SRCS "${LIB_NAME}.cc")
    endif()

    set(LIB_NAME ${LIB_GROUP}_${LIB_NAME})
  endif()

  set(${LIB_NAME}_INCLUDE_DIRS)
  set(${LIB_NAME}_LINK_LIBS)
  foreach(LIB_DEPEND ${LIB_DEPENDS})
    if(NOT TARGET ${LIB_DEPEND})
      message(FATAL_ERROR "${LIB_DEPEND} not a target")
      break()
    endif()
    
    get_target_property(${LIB_DEPEND}_IDIRS ${LIB_DEPEND} INTERFACE_INCLUDE_DIRECTORIES)
    foreach(${LIB_DEPEND}_IDIR ${${LIB_DEPEND}_IDIRS})
      if(EXISTS "${${LIB_DEPEND}_IDIR}" )
	list(APPEND ${LIB_NAME}_INCLUDE_DIRS "${${LIB_DEPEND}_IDIR}")
      endif()	
    endforeach()

    if(LIB_DEPEND MATCHES "(MINIZIP|URIPARSER)")
      list(APPEND LIB_SRCS $<TARGET_OBJECTS:${LIB_DEPEND}>)
    else()
      list(APPEND ${LIB_NAME}_LINK_LIBS ${LIB_DEPEND})
    endif()
    
  endforeach()

  if(LIB_TEST)    
    add_executable(${LIB_NAME} ${LIB_SRCS})
    set_target_properties(${LIB_NAME} PROPERTIES COMPILE_FLAGS "-DGTEST_HAS_RTTI=0")
    target_link_libraries(${LIB_NAME} ${GTEST_LIBRARY})    
    add_test(${LIB_NAME} ${CMAKE_BINARY_DIR}/bin/${LIB_NAME})
  else()
    add_library(${LIB_NAME} ${LIB_SRCS})
  endif()


  #  message("${LIB_NAME}_LINK_LIBS=${${LIB_NAME}_LINK_LIBS}")
  target_link_libraries(${LIB_NAME} ${${LIB_NAME}_LINK_LIBS})
  
  if(${LIB_NAME}_INCLUDE_DIRS)
    list(REMOVE_DUPLICATES ${LIB_NAME}_INCLUDE_DIRS ) 
  endif()
  
  target_include_directories(${LIB_NAME} PUBLIC ${${LIB_NAME}_INCLUDE_DIRS})
  target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src)
  target_include_directories(${LIB_NAME} PUBLIC ${Boost_INCLUDE_DIR})

  if(LIB_TEST)
    target_include_directories(${LIB_NAME} PUBLIC ${GTEST_INCLUDE_DIR})
  endif()
  
  if(LIB_DEPENDS)
    add_dependencies(${LIB_NAME} ${LIB_DEPENDS})
  endif()
 

  if(LIB_DEFS)
    foreach(LIB_DEF ${LIB_DEFS})
      target_compile_definitions(${LIB_NAME} PUBLIC "${LIB_DEF}")
    endforeach()
  endif()
  

  if(NOT LIB_TEST)
    if(VERSION_STRING)
      set_target_properties(${LIB_NAME} PROPERTIES
	VERSION   "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}"
	SOVERSION "${VERSION_MAJOR}")
    endif()
  
    string(REPLACE "kml" "" INCLUDE_DEST_DIR ${LIB_NAME} )
    
    install(FILES ${LIB_INCS}
      DESTINATION ${INCLUDE_INSTALL_DIR}/${INCLUDE_DEST_DIR})
    
    install(TARGETS ${LIB_NAME}
      RUNTIME DESTINATION ${BIN_INSTALL_DIR}
      LIBRARY DESTINATION ${LIB_INSTALL_DIR}
      ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
      )

endif()


endfunction(build_target)

function(build_test)
  cmake_parse_arguments(TEST  "" "GROUP;NAME" "DEPENDS" ${ARGN} )
  message(FATAL_ERROR "TEST_GROUP=${TEST_GROUP} | TEST_NAME=${TEST_NAME}")
endfunction(build_test)

function(build_example)
  cmake_parse_arguments(EXAMPLE  "" "NAME" "LINKS;DEPENDS" ${ARGN} )
  add_executable(example_${EXAMPLE_NAME} ${EXAMPLE_NAME}.cc)
  add_dependencies(example_${EXAMPLE_NAME} ${EXAMPLE_DEPENDS})
  target_link_libraries(example_${EXAMPLE_NAME} ${EXAMPLE_LINKS} ${EXAMPLE_DEPENDS})
endfunction(build_example)


