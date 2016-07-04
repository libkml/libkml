include(ExternalProject)

find_package(Git)
if(NOT WIN32)
  set(ep_base "/tmp/cmake-build/third-party")
else()
  set(ep_base "C:/cmake-build/third-party")
endif()
set_property(DIRECTORY PROPERTY "EP_BASE" ${ep_base})
set(EP_URL "https://github.com/rashadkm")

function(super_find_package name)
  set(PKG_NAME ${name})
  string(TOUPPER ${name} PKG_NAME_)
  set(PKG_REPO ${PKG_NAME})
  set (extra_args ${ARGN})
  list(LENGTH extra_args num_extra_args)
  if (${num_extra_args} GREATER 0)
    list(GET extra_args 0 PKG_REPO)
  endif ()

  set(${PKG_NAME_}_FIND_QUIETLY TRUE)
  find_package(${PKG_NAME})
  if(${PKG_NAME_}_FOUND)
    message(STATUS "[SuperFind] ${PKG_NAME} found from system")
  else()
    if(EXISTS ${ep_base}/Build/${PKG_NAME}/${PKG_NAME}Config.cmake)
      message(STATUS "[SuperFind] ${PKG_NAME} found using config from ${ep_base}/Build/${PKG_NAME}")
      find_package(${PKG_NAME} PATHS ${ep_base}/Build/${PKG_NAME})    
      if(${PKG_NAME_}_FOUND)
	add_custom_target(${PKG_NAME}
          COMMAND ${CMAKE_COMMAND} "--build" "${ep_base}/Build/${PKG_NAME}" 
	  WORKING_DIRECTORY "${ep_base}/Build/${PKG_NAME}")
      endif()
    endif()
  endif()
  
  if(NOT ${PKG_NAME_}_FOUND)
    message(STATUS "[SuperFind] Adding ExternalProject ${PKG_NAME}")    
    ExternalProject_Add(${PKG_NAME}
      GIT_REPOSITORY ${EP_URL}/${PKG_REPO}
      DOWNLOAD_COMMAND ""
      CONFIGURE_COMMAND ""
      UPDATE_COMMAND ""
      INSTALL_COMMAND)
    set(${PKG_NAME}_INSTALL_DIR ${ep_base}/Install/${PKG_NAME})
    
    #download source code.
    if(NOT EXISTS "${ep_base}/Stamp/${PKG_NAME}/${PKG_NAME}-download")
      execute_process(COMMAND git clone --depth 1 ${EP_URL}/${PKG_REPO} ${PKG_NAME}
        WORKING_DIRECTORY  ${ep_base}/Source)
      execute_process(COMMAND ${CMAKE_COMMAND}  -E touch "${PKG_NAME}-download"
        WORKING_DIRECTORY ${ep_base}/Stamp/${PKG_NAME} )  
    endif()
    #configure
    execute_process(COMMAND ${CMAKE_COMMAND} ${ep_base}/Source/${PKG_NAME}
      "-DCMAKE_INSTALL_PREFIX=${${PKG_NAME}_INSTALL_DIR}"
      "-DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS}"
      "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
      "-G${CMAKE_GENERATOR}"
      WORKING_DIRECTORY ${ep_base}/Build/${PKG_NAME} )
    include(${ep_base}/Build/${PKG_NAME}/${PKG_NAME}Config.cmake)    
  endif()

  if(MINGW)
    set(${PKG_NAME}_LIBRARIES ${${PKG_NAME}_LIBRARIES} PARENT_SCOPE)
    set(${PKG_NAME}_LIBRARY ${${PKG_NAME}_LIBRARY} PARENT_SCOPE)
  endif()
endfunction()

macro(add_dependencies_if_needed prefix tgt)  
  if(TARGET ${tgt})
    list(APPEND ${prefix}_DEPENDS ${tgt})
  endif()
endmacro()
