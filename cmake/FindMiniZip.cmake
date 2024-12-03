# Find the Minizip library
# Defines:

#  MINIZIP_INCLUDE_DIR - minizip include directory
#  MINIZIP_LIBRARIES   - minizip libraries
#  MINIZIP_FOUND       - TRUE if minizip is found
#  MiniZip_FOUND       - Same as MINIZIP_FOUND

# Targets:

#  MiniZip::MiniZip

if (MINIZIP_INCLUDE_DIR)
 #check cache 
  set(MINIZIP_FIND_QUIETLY TRUE)
endif ()

if (NOT MINIZIP_INCLUDE_DIR)
    find_path(MINIZIP_INCLUDE_DIR NAMES unzip.h PATH_SUFFIXES minizip)
    set(MINIZIP_INCLUDE_DIR ${MINIZIP_INCLUDE_DIR}/minizip CACHE PATH "minizip includes")
endif ()

find_library(MINIZIP_LIBRARIES NAMES minizip)

if (MINIZIP_INCLUDE_DIR AND MINIZIP_LIBRARIES)
  set(MINIZIP_FOUND TRUE)
  set(MiniZip_FOUND TRUE)
endif ()

if (MINIZIP_FOUND)
   if (NOT MINIZIP_FIND_QUIETLY)
      message(STATUS "Found Minizip library: ${MINIZIP_LIBRARY}")
   endif ()

   if(NOT TARGET MiniZip::MiniZip)
      add_library(MiniZip::MiniZip UNKNOWN IMPORTED)
      set_target_properties(MiniZip::MiniZip PROPERTIES
         INTERFACE_INCLUDE_DIRECTORIES "${MINIZIP_INCLUDE_DIR}"
         IMPORTED_LOCATION "${MINIZIP_LIBRARIES}"
         )
   endif()
else ()
   if (NOT MINIZIP_FIND_QUIETLY)
      message(FATAL_ERROR "Could NOT find Minizip library")
    else ()
      message(STATUS "Could NOT find Minizip library")
    endif ()
endif ()
