#summary Release notes for the 1.2 version of libkml
#labels Featured

# Introduction #

Welcome to the "1.2" release of libkml!

It is the intention of libkml to adhere strictly to the OGC KML 2.2 standard.

# What is libkml? #

This is a library to parse, serialize and programmatically access a KML
document object model (DOM). The main API is C++, and there are SWIG
bindings to Python and Java.

# Who uses libkml? #

We do! Here at Google we regularly process the millions of KML files we crawl using
this software.  We verify correctness of the KML we publish as Google Earth
layers using libkml.  Quite a number of groups within Google use libkml to
parse, create and process KML.

# Licensing #

The libkml software is distributed under the New BSD license, whose text is
found at the top of each file.

# Supported platforms #

This library has been compiled and tested on Windows XP, Mac OS X 10.4 and
10.5, and various flavors of Linux.

# Changes since 1.1 #

  * Upgraded third-party UriParser library to latest version
  * Replaced use of `std::string` with `string` to permit direct use in codebases that have their own (STL-compatible) string implementation
  * Replaced use of `char*` and `XML_Char*` with string in the low-level wrapper around Expat
  * Improved Google Maps and Spreadsheets Data API support
  * Added some support and example programs for CSV files in the Google Maps DATA API
  * Added a callback to the regionator code to allow progress monitoring, cancellation
  * Added option for quadtree-aligned regionation
  * Fixed a spec issue with LatLonBox defaults (now +/- 180, not 0)
  * Smarter serialization of potentially bad CDATA text
  * Windows build fixes
  * A new static lib target in the XCode project
  * Restricted the maximum element nesting depth in XML parsing to 100 (can be overridden at compile time)

# Building and installing libkml #

See the wiki page for BuildingAndInstalling.

# Reference #

See the [Reference](Reference.md).

# Future development #

Some TODO items in the near future may include:

  * Singleton deleter
  * Improve SWIG support

# Found a bug? #

You can file a bug using this project's
[issue tracker](http://code.google.com/p/libkml/issues/list). Please follow
basic [http://www.google.com/search?q=bug+reporting+guidelines bug reporting
procedure] and provide as much information as possible.