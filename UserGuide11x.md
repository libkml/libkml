#summary Release notes for the 1.1 version of libkml
#labels Deprecated

# Introduction #

Welcome to the "1.1" release of libkml!

It is the intention of libkml to adhere strictly to the OGC KML 2.2 standard.

# What is libkml? #

This is a library to parse, serialize and programmatically access a KML
document object model (DOM). The main API is C++, and there are Swig
bindings to Python and Java.

# Who uses libkml? #

We do! We regularly process the millions of KML files crawled by Google using
this software.  We verify correctness of the KML we publish as Google Earth
layers using libkml.  Quite a number of groups within Google use libkml to
parse, create and process KML.

# Licensing #

The libkml software is distributed under the New BSD license, whose text is
found at the top of each file.

# Supported platforms #

This library has been compiled and tested on Windows XP, Mac OS X 10.4 and
10.5, and various flavors of Linux.

# Changes since 1.0 #

  * In-memory KMZ read support
  * Initial Google Maps Data API support
  * Various security fixes, particularly in the underlying Zip library
  * The OS X Framework is much improved

# Building and installing libkml #

See the wiki page for BuildingAndInstalling.

# Reference #

See the [Reference](Reference.md).

# Future development #

Some TODO items in the near future may include:

  * Continued Google Maps Data API support
  * Upgrade of dependent libraries
  * Singleton deleter
  * Improve SWIG support


# Found a bug? #

You can file a bug using this project's
[issue tracker](http://code.google.com/p/libkml/issues/list). Please follow
basic [http://www.google.com/search?q=bug+reporting+guidelines bug reporting
procedure] and provide as much information as possible.