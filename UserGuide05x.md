#summary Release notes for the 0.5 version of libkml
#labels Deprecated

# Introduction #

Welcome to the fifth public release of libkml!

THIS IS ALPHA SOFTWARE. Expect changes. We recommend caution in use in
production code.

This is an initial preview of libkml, and while the general interfaces
described are now fairly stable, there is the potential for change! As KML 2.2
is now an [Open Geospatial Consortium](http://www.opengeospatial.org/) (OGC)
standard, the language itself is now stable. It is the intention of libkml to
adhere strictly to the OGC KML 2.2 standard.

# What is libkml? #

This is a library to parse, serialize and programmatically access a KML
document object model (DOM). The main API is C++, and there are bindings to
Python and Java.

# Who uses libkml? #

We do! We regularly process the millions of KML files crawled by Google using
this software.  We verify correctness of the KML we publish as Google Earth
layers using libkml.

# Licensing #

The libkml software is distributed under the new BSD license, whose text is
found at the top of each file.

# Supported platforms #

This library has been compiled and tested on Windows XP, Mac OS X 10.4 and
10.5, and various flavors of Linux.

# Changes since 0.4 #

  * Usage of cppunit test framework replaced with [googletest](http://googletest.googlecode.com)
  * Mac users can now build all of the libraries in Xcode. There is also a target to build an OS X Framework package. Comments welcome
  * Limited support for transforming GPX files to KML: [example](http://code.google.com/p/libkml/source/browse/trunk/examples/gpx/gpxtracktokml.cc?r=324)
  * Support for parsing and serializing KML 2.2's Atom elements
  * kmldom::Attributes, kmldom::Vec3 classes  moved to kmlbase
  * kmldom::Expat handlers and parser moved to kmlbase
  * KML colors now represented using kmlbase::Color32 class
  * Initial kmlbase::DateTime class
  * Some support for handling old KML 2.1 era Schema usage: [example](http://code.google.com/p/libkml/source/browse/trunk/examples/engine/oldschema.cc?r=324)
  * Numerous other small bug fixes

# Building and installing libkml #

See the wiki page for BuildingAndInstalling.

# Reference #

See the [Reference](Reference.md).

# Future development #

Future development is expect to be on continued expansion of the KML Engine
and Convenience libraries built on the KML DOM in these areas:

  * more complete kmz read and write
  * more object id management
  * more complete xml namespace support
  * networklink fetching
  * feature and geometry bounding box and lookat/camera computation
  * region visibility computation
  * NetworkLinkControl/Update processing

# Found a bug? #

You can file a bug using this project's
[issue tracker](http://code.google.com/p/libkml/issues/list). Please follow
basic [http://www.google.com/search?q=bug+reporting+guidelines bug reporting
procedure] and provide as much information as possible.