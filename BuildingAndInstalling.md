# Building and Installing libkml #

Please read the DEPENDENCIES file carefully and ensure you have the correct
versions of all required software.

There are two separate build systems: one for GNU/Linux and Mac OS X, and
another for Microsoft Windows.

This is last updated for version 1.3.0  There may be changes within the svn tree.

## Linux and Mac OS X ##

We assume you have a cmake 2.8 or higher installed. 
Performing a basic build should be as simple as:

```
git clone https://github.com/libkml/libkml libkml-1.3.0
mkdir libkml-1.3.0.build ; cd libkml-1.3.0.build
cmake ../libkml-1.3.0
```
libkml requires some external libraries. They are listed below in a random order
* boost
* zlib
* minizip
* uriparser
If any of these are found missing, cmake will download and install it automatically!

### Testing (optional) ####
To Enable Testing, you need to pass additional options to your cmake configure step:
```
cd libkml-1.3.0.build
cmake -DBUILD_TESTING=TRUE ../libkml-1.3.0
```

### Examples (optional) ####
To Enable Examples, you need to pass additional options to your cmake configure step:
```
cd libkml-1.3.0.build
cmake -DBUILD_EXAMPLES=TRUE ../libkml-1.3.0
```
#### Build and install ####
```
make
sudo make install
```
### SWIG bindings ###

If you want to create bindings for the additional supported languages, you need
to install the Simplified Wrapper and Interface Generator
([SWIG](http://www.swig.org/)) version 1.3.35.

NOTE: This dependency is not auto-downloaded by cmake

Once SWIG is installed, you can re-run cmake. It will automatically detect swig. But they cmake options that enable bindings are not enabled even if swig is found. This change is made intentionally and not a bug. To activate bindings:
```
cd libkml-1.3.0.build
cmake -DWITH_SWIG=TRUE -DWITH_PYTHON=TRUE -DWITH_JAVA=TRUE ../libkml-1.3.0 
```
The Python bindings, if enabled will be installed to a site-packages directory. 
This will likely be similar to `/usr/local/lib/python2.7/site-packages/`. 
Your `PYTHONPATH` will of course have to know about this directory.


## Microsoft Windows ##
CMake is cross platform and works with a lot of generators. 
It is easy to generate Visual Studio project files using cmake. Check the CMAKE_GENERATOR variable when using cmake-gui.exe on windows. I had tested a build on VS2010. Other versions might work but the case is simply not tested.

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

you can run the tests via ctest no matter what platform you are!

```
ctest 
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
