# Introduction #

Welcome to the second public release of libkml!

THIS IS ALPHA SOFTWARE. Expect changes. We recommend caution in use in production code.

This is an initial preview of libkml, and while the general interfaces described are now
fairly stable, there is the potential for change! As KML 2.2 is now an
[Open Geospatial Consortium](http://www.opengeospatial.org/) (OGC) standard, the language
itself is now stable. It is the intention of libkml to adhere strictly to the OGC KML 2.2
standard.

# What is libkml? #

This is a library to parse, serialize and programmatically access a KML document object
model (DOM). The main API is C++, and there are bindings to Python and Java.

# Who uses libkml? #

We do! We regularly process the millions of KML files crawled by Google using this
software.  We verify correctness of the KML we publish as Google Earth layers using
libkml.

# Licensing #

The libkml software is distributed under the new BSD license, whose text is found at the
top of each file.

# Supported platforms #

This library has been compiled and tested on Windows XP, Mac OS X 10.4 and 10.5, and
various flavors of Linux.

# Changes since 0.1 #

Two main things have changed since 0.1: we have upgraded to a memory management scheme
based on "smart pointers", and we have deprecated the use of SCons. On Linux and Mac OS X we now use the traditional automake, and on Windows we use Microsoft Visual Studio.

Note that the "smart pointer" scheme presently restricts support for alternate language
bindings to Python and Java.

# Building and installing libkml #

Please read the DEPENDENCIES file carefully and ensure you have the correct versions of
all required software.

There are now two separate build systems: one for GNU/Linux and Mac OS X, and another for
Microsoft Windows.

## Linux and Mac OS X ##

We assume you have a reasonable GCC/autotools environment installation. Performing a
basic build should be as simple as:
```
cd libkml-0.2.x
mkdir build
cd build
../configure
make
sudo make install
```

In addition to the usual GNU build system configure options like --prefix, you may
fine-tune the building of libkml as follows. (Use ./configure --help to see all extra
options.)

### SWIG bindings ###

If you want to create bindings for the additional supported languages, you need to install the Simplified Wrapper and Interface Generator ([SWIG](http://www.swig.org/)) version 1.3.35. Once SWIG is installed, the configure program will check for the existence of development versions of Python and Java. If either is found, we attempt to build the SWIG bindings. If you have either language installed in a non-default location, you can specify the location(s) of your headers and libs like so:

```
../configure --with-java-include-dir=DIR \
             --with-java-lib-dir=DIR \
             --with-python-include-dir=DIR \
             --with-python-lib-dir=DIR
```

If possible, SWIG bindings are always built. You can disable this by:

```
../configure --disable-swig
```

Or you can disable specific languages:

```
../configure --disable-java --disable-python
```

By default we do not install the Python SWIG bindings in the system Python extension directory. This is because writing to that directory likely requires root privileges. You can override this behavior like so:

```
../configure --enable-systempython
```

Otherwise, the Python bindings will be installed to a directory relative to configure's prefix. This will likely be similar to `/usr/local/lib/python2.5/site-packages/`. Your `PYTHONPATH` will of course have to know about this directory.


## Microsoft Windows XP ##

We have used Microsoft Visual Studio 2005 to create the project files. The top-level
libkml.sln is the main solution file and will build both the kmldom and kmlutil
libraries. You can also build the examples from the solution file in the examples
directory.


# Running the unit tests #

IMPORTANT: since libkml does not use RTTI, you _must_ configure cppunit accordingly. On Mac OS X the command is `./configure --disable-typeinfo-name`. On Linux the command is: `./configure --disable-typeinfo-name LIBS="-ldl"`. See the top-level DEPENDENCIES file.

The libkml system includes a large suite of unit tests, written against the [CppUnit framework](http://cppunit.sourceforge.net). Once you have have installed CppUnit you can build the tests as follows:

We have provided a large suite of unit tests to verify the correct behavior of libkml. We
use the [CppUnit framework](http://cppunit.sourceforge.net). If you have installed cppunit
in its default location (a prefix of /usr/local) the existence of such should be
discovered automatically. If you have a custom installation, you can specify where the
headers and libraries are installed as:

```
../configure --with-cppunit-prefix=PFX --with-cppunit-exec-prefix=PFX
```

You can run the tests like so:

```
make check
```

The test output looks as follows:

```
make  check-TESTS
AbstractLatLonBoxTest::TestType : OK
AbstractLatLonBoxTest::TestDefaults : OK
AbstractLatLonBoxTest::TestSetToDefaultValues : OK
AbstractLatLonBoxTest::TestSetGetHasClear : OK
OK (4)
...
XsdTest::TestGoodElement : OK
XsdTest::TestBadElement : OK
XsdTest::TestUglyElement : OK
XsdTest::TestGoodEnum : OK
XsdTest::TestBadEnum : OK
XsdTest::TestUglyEnum : OK
OK (6)
PASS: xsd_test
===================
All 43 tests passed
===================
...
make  check-TESTS
KmzTest::TestDataIsKmz : OK
KmzTest::TestReadFileFromKmz : OK
KmzTest::TestReadKmlFromKmz : OK
OK (3)
PASS: kmz_test
==================
All 1 tests passed
==================
```


# Hello libkml #

Here are some small sample programs to show you how to program with libkml.
These are
[parsekml.cc](http://code.google.com/p/libkml/source/browse/trunk/examples/helloworld/parsekml.cc),
[createkml.cc](http://code.google.com/p/libkml/source/browse/trunk/examples/helloworld/createkml.cc),
and
[sortplacemarks.cc](http://code.google.com/p/libkml/source/browse/trunk/examples/helloworld/sortplacemarks.cc)
from the sample suite available [here](http://code.google.com/p/libkml/source/browse/trunk/examples).

```
// parsekml.cc
// This program parses a KML Placemark from a memory buffer and prints
// the value of the <name> element on standard output.

#include <iostream>
#include <string>
#include "kml/dom.h"  // The KML DOM header.

int main() {
  // Parse KML from a memory buffer.
  std::string errors;
  kmldom::ElementPtr element = kmldom::Parse(
    "<kml>"
      "<Placemark>"
        "<name>hi</name>"
        "<Point>"
          "<coordinates>1,2,3</coordinates>"
        "</Point>"
      "</Placemark>"
    "</kml>",
    &errors);

  // Convert the type of the root element of the parse.
  const kmldom::KmlPtr kml = kmldom::AsKml(element);
  const kmldom::PlacemarkPtr placemark = kmldom::AsPlacemark(kml->feature());

  // Access the value of the <name> element.
  std::cout << "The Placemark name is: " << placemark->name()
    << std::endl;
}
```

Another example:

```
// createkml.cc
// This program uses the KmlFactory to create a Point Placemark and
// prints the resultant KML on standard output.

#include <iostream>
#include <string>
#include "kml/dom.h"

// libkml types are in the kmldom namespace
using kmldom::CoordinatesPtr;
using kmldom::KmlPtr;
using kmldom::KmlFactory;
using kmldom::PlacemarkPtr;
using kmldom::PointPtr;

int main() {
  // Get the factory singleton to create KML elements.
  KmlFactory* factory = KmlFactory::GetFactory();

  // Create <coordinates>.
  CoordinatesPtr coordinates = factory->CreateCoordinates();
  // Create <coordinates>-122.0816695,37.42052549<coordinates>
  coordinates->add_point2(-122.0816695,37.42052549);

  // Create <Point> and give it <coordinates>.
  PointPtr point = factory->CreatePoint();
  point->set_coordinates(coordinates);  // point takes ownership

  // Create <Placemark> and give it a <name> and the <Point>.
  PlacemarkPtr placemark = factory->CreatePlacemark();
  placemark->set_name("Cool Statue");
  placemark->set_geometry(point);  // placemark takes ownership

  // Create <kml> and give it <Placemark>.
  KmlPtr kml = factory->CreateKml();
  kml->set_feature(placemark);  // kml takes ownership.

  // Serialize to XML
  std::string xml = kmldom::SerializePretty(kml);

  // Print to stdout
  std::cout << xml;
}
```

This code fragment shows that is is possible to hold references to Elements
in a given parse tree after the reference to the root of this tree is discarded.

```
// sortplacemarks.cc
// This program demonstrates some capabilities of resource management of
// elements in the KML DOM.  An array (std::vector) of PlacemarkPtrs into
// parsed DOM is created.  The DOM root is discarded leaving the only
// references to the underlying Placemarks in the array.  The Placemarks
// are finally discarded when the array goes out of scope.
...
typedef std::vector<PlacemarkPtr> placemark_vector_t;
...
// This function object is used by STL sort() to alphabetize Placemarks
// by <name>.
struct ComparePlacemarks
  : public
      std::binary_function<const PlacemarkPtr&, const PlacemarkPtr&, bool> {
  bool operator()(const PlacemarkPtr& a, const PlacemarkPtr& b) {
    return a->name() < b->name();
  }
};
...
  SavePlacemarks(GetKmlFileRootFeature(argv[1]), &placemark_vector);
  sort(placemark_vector.begin(), placemark_vector.end(), ComparePlacemarks());
  for (size_t i = 0; i < placemark_vector.size(); ++i) {
    cout << i << " " << placemark_vector[i]->id() << " " <<
      placemark_vector[i]->name() << endl;
  }

```

# Example programs #

The libkml system comes with a small suite of [example programs](http://libkml.googlecode.com/svn/trunk/examples/) to help you get started. First build and install libkml as described above.

# Quick reference #

## kmldom ##

The libkml system presently consists of the KML DOM. All classes and functions in the KML DOM are in the kmldom namespace.

## KML 2.2 ##

The libkml DOM implements standard OGC KML 2.2. Google's [KML documentation](http://code.google.com/apis/kml/documentation/) is useful for tutorials, examples, and reference material.

## Creating complex elements ##

Each complex element in KML 2.2 has a C++ type whose name is the same as the element. For example, 

&lt;Placemark&gt;

 is kmldom::PlacemarkPtr, and 

&lt;GroundOverlay&gt;

 is kmldom::GroundOverlayPtr.

The KmlFactory singleton has a method to create each complex element:

```
KmlFactory* factory = kmldom::KmlFactory::GetFactory();
kmldom::PlacemarkPtr placemark = factory->CreatePlacemark();
kmldom::FolderPtr folder = factory->CreateFolder();
```

## Memory management ##

This release of libkml provides "smart pointer" memory management.
As such the factory returns a "smart pointer" to the created Element
and there is a typedef for each pointer to each complex type in the language.
While this is now a value type it is actually still the same size as a regular
pointer and is also used as a pointer.  (Thus upgrading from 0.1 to 0.2 should
simply require changing any `kmldom::Foo*` to `kmldom::FooPtr`, removing any explicit
calls of delete and recompiling).

The "smart pointer" maintains a reference on your behalf to an Element while the pointer remains in scope.  Passing the Element to set it as a child of another Element gives the parent element a reference.  The reference count decreases when either the parent is deleted or when your smart pointer goes out of scope.

To help enforce the tree nature of XML no Element can be set to more than
one parent.   That is, a given Placemark can be added at most once to
a given Folder and never to a 2nd Folder.

Once an element is set to a given parent, it cannot be detached.

The `clear_xxx()` method both removes the child from the parent and releases its
reference to the underlying storage.

The "smart pointer" scheme is compatible with SWIG and as such no particular
memory management operations are required as is traditional in languages
such as Python and Java.

At present the "smart pointer" is simply a standard Boost intrusive\_ptr however
this is not directly considered part of the API.  We strongly encourage
use of the typedefs.

## Setting simple elements ##

Each simple element in KML 2.2 is a field in a complex element. The library provides accessor functions to set, get, clear, and discover the existence of a given simple element.

For example, any Feature (such as Placemark) has a 

&lt;name&gt;

 that can be manipulated with these methods:

```
const std::string& name() const;
bool has_name() const;
void set_name(const std::string& value);
void clear_name();
```

Note that the getter is always `const`.

The `has_xxx()` method returns true if this element was present in the parsed KML or if it was previously set using `set_xxx()`.

The `clear_xxx()` method removes any value set either by the parser or by the `set_xxx()` method. On serialization, no element is emitted for an element that has been cleared.

The getter always returns a value, irrespective of the state returned by `has_xxx()`. If `has_xxx()` is false, then the getter returns the default for this element, as specifed in the KML Reference.

Simple elements are of either `std::string`, `double`, `int`, `boolean` or `enum` type.

Here is how to access the 

&lt;description&gt;

 element:

```
const std::string& name() const;
bool has_name() const;
void set_name(const std::string& value);
void clear_name();
```

Here is how to access the 

&lt;north&gt;

 element:

```
double north() const;
void set_north(double north);
bool has_north() const;
void set_north(bool north);
```

Here is how to access the 

&lt;drawOrder&gt;

 element. Note that the name of the element in the accessor
method is folded to all lower case:

```
int draworder() const;
void set_draworder(bool draworder);
bool has_draworder() const;
void clear_draworder();
```

Here is how to access the 

&lt;visibility&gt;

 element:

```
bool visibility() const;
void set_visibility(bool visibility);
bool has_visibility() const;
void clear_visibility();
```

Here is how to access the 

&lt;altitudeMode&gt;

 element:

```
int altitudemode() const;
void set_altitudemode(int altitudemode);
bool has_altitudemode() const;
void clear_altitudemode();
```

## Enumerated value elements ##

Every enumerated value element has a C++ `enum`. For example, here is the `enum` for 

&lt;altitudeMode&gt;

:

```
typedef enum {
  ALTITUDEMODE_CLAMPTOGROUND = 0,
  ALTITUDEMODE_RELATIVETOGROUND,
  ALTITUDEMODE_ABSOLUTE
} AltitudeModeEnum;
```

The `enum` type name is the element name with a leading capital and the string 'Enum' appended to it. Thus 

&lt;colorMode&gt;

 is of ColorModeEnum, and 

&lt;listItemType&gt;

 is ListItemTypeEnum.

## More on complex elements ##

There are 3 kinds of complex child accessors: 1) single value of a specific type, 2) single value of a group type, and 3) an array value of either a specific or group type. Here are examples of each.

The 

&lt;LatLonBox&gt;

 child of 

&lt;GroundOverlay&gt;

 is an example of a complex child of a specific type:

```
const LatLonBoxPtr& latlonbox() const;
void set_latlonbox(const LatLonBoxPtr& latlonbox);
bool has_latlonbox() const;
void clear_latlonbox();
```

The AbstractView child of Feature is an example of a complex child of a group type. Both 

&lt;LookAt&gt;

 and 

&lt;Camera&gt;

 can be used with these accessors.

```
const AbstractViewPtr& abstractview() const;
void set_abstractview(const AbstractViewPtr& abstractview);
bool has_abstractview() const;
void clear_abstractview();
```

The Feature child of 

&lt;Folder&gt;

 is an example of an array value of a group type:

```
void add_feature(const FeaturePtr& feature);
size_t feature_array_size() const;
const kmldom::FeaturePtr& feature_array_at(unsigned int index) const;
```

(Note that in KML 2.2 the following elements are all of Feature type: Placemark, NetworkLink, GroundOverlay, ScreenOverlay, PhotoOverlay, Folder, and Document)

## Type inspection and conversion ##

All complex elements are derived from `kmldom::Element`. There is a type conversion and an inspection function for each complex type. The libkml system is not built with run-time type information (RTTI), hence `dynamic_cast` is not used. If the element is of the desired type, then a pointer of that type is returned, else NULL.

For example, the following code accesses the Geometry of a Placemark to discover if it is a Point:

```
const kmldom::PlacemarkPtr placemark;
...
if (placemark->has_geometry()) {
  if (const kmldom::PointPtr point = kmldom::AsPoint(placemark->geometry()) {
    // Yes, it is a Point... see if it has coordinates:
    if (point->has_coordinates()) {
      ...
    }
  }
}
```

Every element has a type id that can be accessed with the Type() method:

```
const FeaturePtr feature = kml->feature();
if (feature->Type() == Type_Placemark) {
  // Yes, this is a Placemark
}
```

Every element has an IsA() method to inquire the specific or group type of an element:

```
GroundOverlayPtr overlay = KmlFactory()->CreateGroundOverlay();
assert(overlay->IsA(kmldom::Type_Object));
assert(overlay->IsA(kmldom::Type_Feature));
assert(overlay->IsA(kmldom::Type_Overlay));
assert(overlay->IsA(kmldom::Type_GroundOverlay));
```

# Future development #

With this 0.2 release we hope to soon freeze the API to the kmldom namespace.
Future development will be on the KML "Engine" built on the KML DOM.

  * full kmz read and write
  * object id management
  * xml namespace support
  * style resolution
  * balloon template expansion
  * networklink fetching
  * feature and geometry bounding box and lookat/camera computation
  * region visibility computation
  * NetworkLinkControl/Update processing
  * regionator framework

# Found a bug? #

You can file a bug using this project's [issue tracker](http://code.google.com/p/libkml/issues/list). Please follow basic [bug reporting procedure](http://www.google.com/search?q=bug+reporting+guidelines) and provide as much information as possible.