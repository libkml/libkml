# Install the find modules so consumers of libkml can find its dependencies.
install(
    FILES
        FindMiniZip.cmake
        FindUriParser.cmake
    DESTINATION
        ${DEF_INSTALL_CMAKE_DIR}
)

