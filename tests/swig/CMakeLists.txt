if(WITH_PYTHON)
add_test(NAME test_python_kmlbase
  COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/kmlbase_test.py)
set_tests_properties(test_python_kmlbase
     PROPERTIES ENVIRONMENT "PYTHONPATH=${CMAKE_BINARY_DIR}/src/swig:${CMAKE_BINARY_DIR}/lib")

add_test(NAME test_python_kmldom
  COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/kmldom_test.py)
set_tests_properties(test_python_kmldom
     PROPERTIES ENVIRONMENT "PYTHONPATH=${CMAKE_BINARY_DIR}/src/swig:${CMAKE_BINARY_DIR}/lib")

add_test(NAME test_python_kmlengine
  COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/kmlengine_test.py)
set_tests_properties(test_python_kmlengine
     PROPERTIES ENVIRONMENT "PYTHONPATH=${CMAKE_BINARY_DIR}/src/swig:${CMAKE_BINARY_DIR}/lib")
endif()

if(WITH_JAVA)
include(UseJava)
include(JUnit)
find_file(JUNIT_JAR NAMES junit.jar PATHS ${JAVA_LIB_INSTALL_DIR} /usr/share/java)
find_file(HAMCREST_JAR NAMES hamcrest/core.jar PATHS ${JAVA_LIB_INSTALL_DIR} /usr/share/java)

add_jar(KmlBaseTest KmlBaseTest.java INCLUDE_JARS /usr/share/java/junit.jar ${CMAKE_BINARY_DIR}/src/swig/LibKML.jar)
add_dependencies(KmlBaseTest LibKML_jar)

if(WIN32 AND NOT CYGWIN)
    set(PATH_SEPARATOR ";")
else(WIN32 AND NOT CYGWIN)
    set(PATH_SEPARATOR ":")
endif(WIN32 AND NOT CYGWIN)

add_junit_test(test_java_kmlbase CLASSPATH "${JUNIT_JAR}${PATH_SEPARATOR}${HAMCREST_JAR}${PATH_SEPARATOR}${CMAKE_BINARY_DIR}/src/swig/LibKML.jar${PATH_SEPARATOR}${CMAKE_CURRENT_BINARY_DIR}/KmlBaseTest.jar" TESTS KmlBaseTest)
set_tests_properties(test_java_kmlbase
     PROPERTIES ENVIRONMENT "LD_LIBRARY_PATH=${CMAKE_BINARY_DIR}/lib")
endif()
