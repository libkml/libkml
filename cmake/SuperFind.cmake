function(super_find_package name)
  set(PKG_NAME ${name})
  set(PKG_REPO ${PKG_NAME})
  set (extra_args ${ARGN})
  list(LENGTH extra_args num_extra_args)
  if (${num_extra_args} GREATER 0)
    list(GET extra_args 0 PKG_REPO)
  endif ()

  if(EXISTS ${ep_base}/Build/${PKG_NAME}/${PKG_NAME}Config.cmake)
    message(STATUS "[FIND_PACKAGE ${PKG_NAME} ] using config from ${ep_base}/Build/${PKG_NAME}")
    find_package(${PKG_NAME} PATHS ${ep_base}/Build/${PKG_NAME})
  else()
    message(STATUS "[FIND_PACKAGE ${PKG_NAME} ] no config")
    find_package(${PKG_NAME} )
  endif()
  
  if(NOT ${PKG_NAME}_FOUND)    
    ExternalProject_Add(${PKG_NAME}
      GIT_REPOSITORY ${EP_URL}/${PKG_REPO}
      DOWNLOAD_COMMAND ""
      CONFIGURE_COMMAND ""
      UPDATE_COMMAND ""        
      INSTALL_COMMAND
      )
    
    set(${PKG_NAME}_INSTALL_DIR ${ep_base}/Install/${PKG_NAME})
    
    if(NOT EXISTS "${ep_base}/Stamp/${PKG_NAME}/${PKG_NAME}-download")

      execute_process(COMMAND git clone ${EP_URL}/${PKG_REPO} ${PKG_NAME}
        WORKING_DIRECTORY  ${ep_base}/Source)
      
      execute_process(COMMAND ${CMAKE_COMMAND}  -E touch "${PKG_NAME}-download"
        WORKING_DIRECTORY ${ep_base}/Stamp/${PKG_NAME} )  
    endif()
    
    execute_process(COMMAND ${CMAKE_COMMAND} ${ep_base}/Source/${PKG_NAME}
      "-DCMAKE_INSTALL_PREFIX=${${PKG_NAME}_INSTALL_DIR}"
      WORKING_DIRECTORY ${ep_base}/Build/${PKG_NAME} )

    include(${ep_base}/Build/${PKG_NAME}/${PKG_NAME}Config.cmake)
    
  endif()

endfunction()

