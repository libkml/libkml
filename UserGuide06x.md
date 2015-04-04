#summary Release notes for the 0.6 version of libkml
#labels Deprecated

# Introduction #

Welcome to the sixth public release of libkml!

THIS IS ALPHA SOFTWARE. Expect changes. We recommend caution in use in
production code.

This is a development shapshot of libkml, and while the general interfaces
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

# Changes since 0.5 #

  * KmlStream streamed parsing
  * Support for Update/Change,Create
  * KmlFile DOM import
  * Limited support for KML 2.2's xAL elements.
  * Support for kmldom and kmlengine unit tests on MS Windows
  * Numerous other small bug fixes

# Building and installing libkml #

See the wiki page for BuildingAndInstalling.

# Reference #

See the [Reference](Reference.md).

# Future development #

These are some items anticipating development in the very near future:

  * KMZ creation
  * Update/Delete processing
  * upgrade dependent libraries
  * TODO cleanup

# Found a bug? #

You can file a bug using this project's
[issue tracker](http://code.google.com/p/libkml/issues/list). Please follow
basic [http://www.google.com/search?q=bug+reporting+guidelines bug reporting
procedure] and provide as much information as possible.