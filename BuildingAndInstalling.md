# Building and Installing libkml #

Please read the DEPENDENCIES file carefully and ensure you have the correct
versions of all required software.

There are two separate build systems: one for GNU/Linux and Mac OS X, and
another for Microsoft Windows.

This is last updated for version 0.6.1.  There may be changes within the svn tree.

## Linux and Mac OS X ##

We assume you have a reasonable GCC/autotools environment installation.
Performing a basic build should be as simple as:

```
cd libkml-0.x.x
mkdir build
cd build
../configure
make
sudo make install
```

In addition to the usual GNU build system configure options like --prefix, you
may fine-tune the building of libkml as follows. (Use ./configure --help to see
all extra options.)

### SWIG bindings ###

If you want to create bindings for the additional supported languages, you need
to install the Simplified Wrapper and Interface Generator
([SWIG](http://www.swig.org/)) version 1.3.35.

NOTE: the Microsoft Windows Visual Studio .vcproj's do not build SWIG.

Once SWIG is installed, the
configure program will check for the existence of development versions of
Python and Java. If either is found, we attempt to build the SWIG bindings. If
you have either language installed in a non-default location, you can specify
the location(s) of your headers and libs like so:

```
../configure --with-java-include-dir=DIR \
             --with-java-lib-dir=DIR \
             --with-python-include-dir=DIR \
             --with-python-lib-dir=DIR
```

It is likely that the Python installation and headers will be discovered
automatically. If you want to build the Java bindings you will almost
certainly have to tell configure where to find the headers it needs.

For Mac OS X the command is probably quite close to this:
```
../configure --with-java-include-dir=/System/Library/Frameworks/JavaVM.framework/Headers
```

For Linux is it is something like:
```
../configure --with-java-include-dir=/usr/lib/jvm/include
```

If possible, SWIG bindings are always built. You can disable this by:

```
../configure --disable-swig
```

Or you can disable specific languages:

```
../configure --disable-java --disable-python
```

By default we do not install the Python SWIG bindings in the system Python
extension directory. This is because writing to that directory likely requires
root privileges. You can override this behavior as follows. Installation must
then be performed by `sudo make install`.

```
../configure --enable-systempython
```

Otherwise, the Python bindings will be installed to a directory relative to
configure's prefix. This will likely be similar to
`/usr/local/lib/python2.5/site-packages/`. Your `PYTHONPATH` will of course
have to know about this directory.


## Microsoft Windows XP ##

We have used Microsoft Visual Studio 2005 to create the project files. The
top-level libkml.sln is the main solution file and will build all libraries in
the libkml system. You can also build the examples from the solution file
in the examples directory.

(It is known that Microsoft Visual Studio 2008 does not work with libkml)

# Running the unit tests #

It is HIGHLY recommended that you build and run all unit tests.
We consider the unit tests of libkml as important as the code itself
given these assert semantics about the KML language itself and not
just the libkml system.  You will note that the unit tests for a given
module often far exceed that module in raw lines of code.

## Build and run the libkml unit tests ##

We have provided a large suite of unit tests to verify the correct behavior of
libkml. We use the [GoogleTest framework](http://googletest.googlecode.com), which
on Linux and Mac OS X is built automatically as a part of the automake process and is
supplied in binary form for MS Windows.

On Linux/OS X you can run the tests like so:

```
make check
```

On Windows you should first build the libkml libraries and then the tests solution. There is a batch script that runs the tests:

```
cd msvc\tests
exec_tests.bat
```

Excerpts of the test output looks as follows.

In reporting any problem with libkml please also submit a complete
trace of your run of the unit test suite.

```
make  check-TESTS
[==========] Running 10 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 10 tests from AttributesTest
[ RUN      ] AttributesTest.TestCreate
[       OK ] AttributesTest.TestCreate
[ RUN      ] AttributesTest.TestCreateOdd
[       OK ] AttributesTest.TestCreateOdd
[ RUN      ] AttributesTest.TestSetGetString
[       OK ] AttributesTest.TestSetGetString
[ RUN      ] AttributesTest.TestSetGetDouble
[       OK ] AttributesTest.TestSetGetDouble
[ RUN      ] AttributesTest.TestSetGetInt
[       OK ] AttributesTest.TestSetGetInt
[ RUN      ] AttributesTest.TestClone
[       OK ] AttributesTest.TestClone
[ RUN      ] AttributesTest.TestMerge
[       OK ] AttributesTest.TestMerge
[ RUN      ] AttributesTest.TestSerialize
[       OK ] AttributesTest.TestSerialize
[ RUN      ] AttributesTest.TestMatch
[       OK ] AttributesTest.TestMatch
[ RUN      ] AttributesTest.TestMatchNoDefault
[       OK ] AttributesTest.TestMatchNoDefault
[----------] Global test environment tear-down
[==========] 10 tests from 1 test case ran.
[  PASSED  ] 10 tests.
PASS: attributes_test
...
PASS: xsd_util_test
[==========] Running 2 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 2 tests from XstParserTest
[ RUN      ] XstParserTest.TestParseXstAlias
[       OK ] XstParserTest.TestParseXstAlias
[ RUN      ] XstParserTest.TestParseXst
[       OK ] XstParserTest.TestParseXst
[----------] Global test environment tear-down
[==========] 2 tests from 1 test case ran.
[  PASSED  ] 2 tests.
PASS: xst_parser_test
==================
All 9 tests passed
==================
```

Some amount of Python SWIG functionality is tested in src/swig/kmldom\_test.py
and src/swig/kmlengine\_test.py. A successful run of these tests looks as follows:

```
.......................................
----------------------------------------------------------------------
Ran 39 tests in 0.013s

OK
```

And so on. If any tests fail to pass, you will be asked to report the issue to
this project's issue tracker.