# Introduction #

Welcome to the first public PREVIEW release of libkml!

THIS IS ALPHA SOFTWARE. Expect changes. We do not yet recommend use in production code.

This is an initial preview of libkml, and while the general interfaces described are now fairly stable, there is the potential for change! As a result of KML 2.2 advancing through the [Open Geospatial Consortium](http://www.opengeospatial.org/) (OGC) to become a standard, the language itself is now stable. It is the intention of libkml to adhere strictly to the OGC KML 2.2 standard.

# What is libkml? #

This is a library to parse, serialize and programmatically access a KML document object model (DOM). The main API is C++, and there are bindings to Python, Ruby, PHP, Perl, and Java.

# Licensing #

The libkml software is distributed under the new BSD license, whose text is found at the top of each file.

# Supported platforms #

This library has been compiled and tested on Windows XP, Mac OS X 10.4 and 10.5, and various flavors of Linux.

# Building and installing libkml #

To build and install libkml from source you first need to install [SCons version 0.97](http://www.scons.org/).

For many people, building libkml from source will be as simple as typing:

```
scons
```

Use the PREFIX argument as follows to install libkml in a location other than the default:

```
scons PREFIX=/your/root install
```

You may also use LIBDIR and INCDIR to specify completely separate lib and include directories.

[Expat version 2.0.1](http://expat.sourceforge.net/) is the XML parser used in libkml, and must be installed separately. You tell SCons where to find the Expat library and header files like so:

```
scons EXPAT_LIBDIR=/your/root/lib EXPAT_INCDIR=/your/root/include
```

Note: on Linux and Mac, we try to make reasonable guesses at whether your system will prefer /usr or /usr/local as a prefix to the default include and lib directories it takes as defaults. If we find expat.h at /usr/include, we assume the /usr prefix for all other third-party system libraries and headers. You can override this with the explicit command line flags seen by running `scons -h`.

If you want to create bindings for the additional supported languages, you need to install the Simplified Wrapper and Interface Generator ([SWIG](http://www.swig.org/)) version 1.3.33. Once SWIG is installed the language bindings are created by default. You may explicitly disable the building of the SWIG extensions by using the RUNSWIG option in SCons as follows:

```
scons RUNSWIG=0  # 0 means to not run SWIG to build scripting language bindings
```

# Running the unit tests #

IMPORTANT: since libkml does not use RTTI, you _must_ configure cppunit accordingly. On Mac OS X the command is `./configure --disable-typeinfo-name`. On Linux the command is: `./configure --disable-typeinfo-name LIBS="-ldl"`. See the top-level DEPENDENCIES file.

The libkml system includes a large suite of unit tests, written against the [CppUnit framework](http://cppunit.sourceforge.net). Once you have have installed CppUnit you can build the tests as follows:

```
scons CPPUNIT_LIBDIR=/your/root/lib CPPUNIT_INCDIR=/your/root/include
```

Note: on Linux and Mac, CPPUNIT\_INCDIR defaults to /usr/local/include and CPPUNIT\_LIBDIR defaults to /usr/local/lib. This matches CppUnit's own installation defaults.

To run the tests, invoke SCons as follows:

```
scons runtests
```

The test output looks as follows:

```
...
kmz_test PASSED (Test Binaries: 1 passed, 0 failed)
...
abstractlatlonbox_test PASSED (Test Binaries: 2 passed, 0 failed)
...
...
xsd_test PASSED (Test Binaries: 42 passed, 0 failed)
...
```

# Hello libkml #

Here are some small sample programs to show you how to program with libkml.
These are
[parsekml.cc](http://code.google.com/p/libkml/source/browse/trunk/examples/helloworld/parsekml.cc)
and
[createkml.cc](http://code.google.com/p/libkml/source/browse/trunk/examples/helloworld/createkml.cc)
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
  kmldom::Element* element = kmldom::Parse(
    "<Placemark><name>hi</name></Placemark>",
    &errors);

  // Convert the type of the root element of the parse.
  const kmldom::Placemark* placemark = kmldom::AsPlacemark(element);

  // Access the value of the  element.
  std::cout << "The Placemark name is: " << placemark->name()
    << std::endl;

  // Release memory
  delete element;
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
using kmldom::Coordinates;
using kmldom::Kml;
using kmldom::KmlFactory;
using kmldom::Placemark;
using kmldom::Point;

int main() {
  // Get the factory singleton to create KML elements.
  KmlFactory* factory = KmlFactory::GetFactory();

  // Create <coordinates>.
  Coordinates* coordinates = factory->CreateCoordinates();
  // Create <coordinates>-122.0816695,37.42052549<coordinates>
  coordinates->add_point2(-122.0816695,37.42052549);

  // Create <Point> and give it <coordinates>.
  Point* point = factory->CreatePoint();
  point->set_coordinates(coordinates);  // point takes ownership

  // Create <Placemark> and give it a <name> and the <Point>.
  Placemark* placemark = factory->CreatePlacemark();
  placemark->set_name("Cool Statue");
  placemark->set_geometry(point);  // placemark takes ownership

  // Create <kml> and give it <Placemark>.
  Kml* kml = factory->CreateKml();
  kml->set_feature(placemark);  // kml takes ownership.

  // Serialize to XML
  std::string xml = kmldom::SerializePretty(*kml);

  // Print to stdout
  std::cout << xml;

  // Release memory
  delete kml;  // Frees all child elements
}
```

# Example programs #

The libkml system comes with a small suite of [example programs](http://libkml.googlecode.com/svn/trunk/examples/) to help you get started. First build and install libkml as described above. Then build the 'helloworld' examples as follows:

```
cd examples/helloworld
scons LIBKML_LIBDIR=/your/root/lib LIBKML_INCDIR=/your/root/include
```

If you do not supply an explicit LIBKML\_LIBDIR or LIBKML\_INCDIR, the libraries and headers in the build directory will be used.

# Quick reference #

## kmldom ##

The libkml system presently consists of the KML DOM. All classes and functions in the KML DOM are in the kmldom namespace.

## KML 2.2 ##

The libkml DOM implements KML 2.2, which is currently pending acceptance as an OGC Standard. Google's [KML documentation](http://code.google.com/apis/kml/documentation/) is useful for tutorials, examples, and reference material.

## Creating complex elements ##

Each complex element in KML 2.2 has a C++ type whose name is the same as the element. For example, 

&lt;Placemark&gt;

 is kmldom::Placemark, and 

&lt;GroundOverlay&gt;

 is kmldom::GroundOverlay.

The KmlFactory singleton has a method to create each complex element:

```
KmlFactory* factory = kmldom::KmlFactory::GetFactory();
kmldom::Placemark* placemark = factory->CreatePlacemark();
kmldom::Folder* folder = factory->CreateFolder();
```

## Memory management ##

This PREVIEW release of libkml provides no automatic memory management.
Thus special consideration is required to prevent memory leaks and corruption.
Future revisions of libkml may offer more sophistication in this
area such as the facilities of "smart pointers", etc.

The general rules are that anything returning a non-const Element is also
handing you ownership and anything returning a const Element is retaining
ownership.  Thus you must either delete any non-const Element you are
handed (such as from the factory) or you must attach the Element to another
via that Element's set or add method.

(In this discussion Element refers to any type derived from Element such
as all KML complex elements.  For example, Placemark is an Element,
Folder is an Element, etc.)

You own an Element until such time that you delete it or pass it to a
`set_xxx()` or `add_xxx()`method of another Element.  For example,
passing a placemark to folder->add\_feature(placemark) gives up ownership
to that folder.  The folder will delete all of its children when the folder is deleted.

To help enforce the tree nature of XML no Element can be set to more than
one parent.   That is, a given Placemark can be added at most once to
a given Folder and never to a 2nd Folder.

Once an element is set to a given parent, it cannot be detached.  The getter
will return a const "read-only" view of the element, but as the const nature
suggests it can no longer be altered.  (Full read-write capability of the KML DOM
is envisioned for future versions).

The `clear_xxx()` method both removes the child from the parent and releases its storage.
As always any deletion of an element also releases the storage of all of its children.
Any pointers into the hierarchy of elements rooted at the deleted element must
no longer be used. Future KML DOM enhancements may include "smart pointers"
that reference count such usage.

For the benefit of permitting memory management of the underlying DOM through
the SWIG interface, the following method is also available to delete a given element
and its children:

```
factory->DeleteElement(placemark);
factory->DeleteElement(folder);
```

The KML DOM in this PREVIEW 0.1 version has two overall main patterns of use:
1) parse and examine, 2) bottom-up creation.  Both result in a KML Element hierachy
that can be walked and serialized.  Neither permits fine-grain editting.  The general
pattern for "bottom-up creation" is to create the children and set their fields before
attaching them to a parent: for example, you create a Coordinates, set the points, then
give that to a Point and in turn give the Point to a Placemark which in turn is
given to a Folder, for example.

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

Note that the `get_xxx()` method for a complex element returns a `const` pointer. This is to help indicate that the element is owned by the parent and cannot be manipulated further.

There are 3 kinds of complex child accessors: 1) single value of a specific type, 2) single value of a group type, and 3) an array value of either a specific or group type. Here are examples of each.

The 

&lt;LatLonBox&gt;

 child of 

&lt;GroundOverlay&gt;

 is an example of a complex child of a specific type:

```
const LatLonBox* latlonbox() const;
void set_latlonbox(LatLonBox* latlonbox);
bool has_latlonbox() const;
void clear_latlonbox();
```

The AbstractView child of Feature is an example of a complex child of a group type. Both 

&lt;LookAt&gt;

 and 

&lt;Camera&gt;

 can be used with these accessors.

```
const AbstractView* abstractview() const;
void set_abstractview(AbstractView* abstractview);
bool has_abstractview() const;
void clear_abstractview();
```

The Feature child of 

&lt;Folder&gt;

 is an example of an array value of a group type:

```
void add_feature(Feature* feature);
size_t feature_array_size() const;
const kmldom::Feature* feature_array_at(unsigned int index) const;
```

(Note that in KML 2.2 the following elements are all of Feature type: Placemark, NetworkLink, GroundOverlay, ScreenOverlay, PhotoOverlay, Folder, and Document)

## Type inspection and conversion ##

All complex elements are derived from `kmldom::Element`. There is a type conversion and an inspection function for each complex type. The libkml system is not built with run-time type information (RTTI), hence `dynamic_cast` is not used. If the element is of the desired type, then a pointer of that type is returned, else NULL.

For example, the following code accesses the Geometry of a Placemark to discover if it is a Point:

```
const Placemark* placemark;
...
if (placemark->has_geometry()) {
  if (const kmldom::Point* point = kmldom::AsPoint(placemark->geometry()) {
    // Yes, it is a Point... see if it has coordinates:
    if (point->has_coordinates()) {
      ...
    }
  }
}
```

Every element has a type id that can be accessed with the Type() method:

```
const Feature* feature = kml->feature();
if (feature->Type() == Type_Placemark) {
  // Yes, this is a Placemark
}
```

Every element has an IsA() method to inquire the specific or group type of an element:

```
GroundOverlay* overlay = KmlFactory()->CreateGroundOverlay();
assert(overlay->IsA(kmldom::Type_Object));
assert(overlay->IsA(kmldom::Type_Feature));
assert(overlay->IsA(kmldom::Type_Overlay));
assert(overlay->IsA(kmldom::Type_GroundOverlay));
```

# Future development #

As the PREVIEW language and "0.1" numerology indicates, we have much more in mind for the future.

While parsing to, serializing from, and programmatic access to the raw KML DOM are reasonably useful operations that encode some important KML semantics, there are higher-level semantics and functionality of KML that aren't yet supported.
These include resolving the Style for a Feature, expanding the balloon text,
managing the id's in a KML file, fetching a NetworkLink,
finding the Features in a given bounding box, etc.

We intend to offer a variety of enhancements such as these higher-level semantics
and processing functionality in future releases of libkml.

# Found a bug? #

You can file a bug using this project's [issue tracker](http://code.google.com/p/libkml/issues/list). Please follow basic [bug reporting procedure](http://www.google.com/search?q=bug+reporting+guidelines) and provide as much information as possible.