add_subdirectory(base)
add_subdirectory(dom)
add_subdirectory(xsd)
add_subdirectory(engine)
add_subdirectory(convenience)
add_subdirectory(regionator)

set(LIBKML_TARGETS "${LIBKML_TARGETS}" PARENT_SCOPE)

install(  FILES dom.h engine.h
          DESTINATION ${INCLUDE_INSTALL_DIR}
          COMPONENT Development)

        