#summary libkml base reference

# KML Base #

All classes and functions in the KML Base are in the kmlbase namespace.

This module contains base functionality used in kmldom and above.
There is nothing directly specific to KML or KMZ in this module.

Here is an overview of the KML Base functions and classes:

  * Attributes - manage XML attributes
  * Color32 - manage the abgr color type used in KML
  * DateTime - manage the time format used in KML
  * Expat - C++ wrapper to XML parser
  * File - platform independent local file I/O
  * Math utils - Great Circle math utilities
  * NetCache
  * Referent - boost::intrusive\_ptr support
  * String typedefs and utils
  * UriParser - C++ wrapper for URI resolution library
  * Vec3 - manage 2d and 3d points
  * Version - get libkml version info
  * XML namespaces - get common XML namespaces and aliases

## Attributes ##

The kmlbase::Attributes class provides methods to parse Expat-style
attribute lists, query and change attributes, and format them as XML.

Here are some examples of some of the capabilities.

See
[kml/base/attributes.h](http://code.google.com/p/libkml/source/browse/trunk/src/kml/base/attributes.h)
for detailed information.

Parsing and inspecting...

```
// This is how Expat's startElement method passes in an element's attributes.
const char* expat_attrs[] = { "type", "double", "name", "TrailLength", 0 };
kmlbase::Attributes* attributes = kmlbase::Attributes::Create(expat_attrs);
std::string type;
attributes->GetValue("type", &type);
std::string name;
attributes->GetValue("name", &name);
delete attributes;  // Better might be scoped_ptr<Attributes>
```

Creating and XML formatting...

```
Attributes attributes;
attributes.SetValue("x", .75);
attributes.SetValue("yunits", "fraction");
std::string xml;
attributes.Serialize(&xml);
```

## DateTime ##

The !kmlbase::DateTime class parses the time formats used in KML.

See
[kml/base/date\_time.h](http://code.google.com/p/libkml/source/browse/trunk/src/kml/base/date_time.h)
for detailed information.

A parsing example...

```
kmlbase::DateTime* date_time = kmlbase::DateTime::Create("2008-10-03T09:25:42Z");
std::string hms = date_time->GetXsdTime();
std::string ymd = date_time->GetXsdDate();
delete date_time;  // Consider scoped_ptr<DateTime>
```

## Expat C++ ##

The ExpatHandler, ExpatHandlerNs and ExpatParser classes provide a C++
front-end to the underlying Expat parser.

See
[kml/base/expat\_parser.h](http://code.google.com/p/libkml/source/browse/trunk/src/kml/base/expat_parser.h)
for detailed information.

## File I/O ##

The File class provides a set of methods for OS-agnostic basic local file I/O.

See
[kml/base/file.h](http://code.google.com/p/libkml/source/browse/trunk/src/kml/base/file.h)
for detailed information.

```
std::string file_content;
kmlbase::File::ReadFileToString("some-file", &file_content);
```

## Math utils ##

There are some math utils in
[kml/base/math\_util.h](http://code.google.com/p/libkml/source/browse/trunk/src/kml/base/math_util.h).

## Networking ##

The NetFetcher and NetCache classes provide and interface between libkml
and your networking code.

See
[kml/base/net\_cache.h](http://code.google.com/p/libkml/source/browse/trunk/src/kml/base/net_cache.h)
for detailed information.

See
[curlfetch.h](http://code.google.com/p/libkml/source/browse/trunk/examples/hellonet/curlfetch.h)
for an example implementation based on libcurl.

## Referent ##

The Referent class implements the reference counter for boost::intrustive\_ptr.

See
[kml/base/referent.h](http://code.google.com/p/libkml/source/browse/trunk/src/kml/base/referent.h)
for detailed information.

All KML elements in libkml ultimately derive from kmlbase::Referent.

## String utils ##

The KML Base includes some string utilities particular to higher level
operations in KML.

See
[kml/base/string\_util.h](http://code.google.com/p/libkml/source/browse/trunk/src/kml/base/string_util.h)
for detailed information.

## UriParser C++ ##

The UriParser class provides a C++ front-end to the internal URI
parsing and resolution library.

For KMZ-aware URI processing see
[kml/engine/kml\_uri.h](http://code.google.com/p/libkml/source/browse/trunk/src/kml/engine/kml_uri.h).

## Vec3 ##

A !Vec3 represents a 2d or 3d point.

See
[kml/base/vec3.h](http://code.google.com/p/libkml/source/browse/trunk/src/kml/base/vec3.h)
for detailed information.

## Version ##

The Version class provides an API to the version of a compiled library.

The kml/base/version.h header provides the macro definitions to compile
into your application code.

For example:

```
// your-code.cc
#include "kml/base/version.h"

if (LIBKML_MAJOR_VERSION == kmlbase::Version::GetMajor() &&
    LIBKML_MINOR_VERSION == kmlbase::Version::GetMinor() &&
    LIBKML_MINOR_VERSION == kmlbase::Version::GetMcro()) {
  std::cout << "this code built with same release as the library" << std::endl;
}
```

## XML namespaces ##

The KML Base includes a set of XML namespaces and aliases (prefixes)
and mappings to a simple enum for a set of languages related to KML.

See
[kml/base/xml\_namespaces.h](http://code.google.com/p/libkml/source/browse/trunk/src/kml/base/xml_namespaces.h)
for detailed information.

For example, the following...

```
std::string atom_prefix;
std::string atom_namespace;
FindXmlNamespaceAndPrefix(XMLNS_ATOM, &atom_prefix, &atom_namespace);
std::cout << "Atom alias: " << atom_prefix << std::endl;
std::cout << "Atom namespace: " << atom_namespace << std::endl;
```

...outputs...

```
Atom alias: atom
Atom namespace: http://www.w3.org/2005/Atom
```
