#summary Release notes for the 0.3 version of libkml
#labels Deprecated

# Introduction #

Welcome to the third public release of libkml!

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

# Changes since 0.2 #

The KML DOM is enhanced since 0.2 but remains compatible.
Since 0.2 there are there are now 3 new libraries:

  * KML Engine
  * KML Convenience
  * KML Regionator

The internal "util" library has been renamed KML base.

# Building and installing libkml #

See the wiki page for BuildingAndInstalling.

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
  const kmldom::PlacemarkPtr placemark =
    kmldom::AsPlacemark(kml->get_feature());

  // Access the value of the <name> element.
  std::cout << "The Placemark name is: " << placemark->get_name()
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
  coordinates->add_latlng(37.42052549,-122.0816695);;

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
    return a->get_name() < b->get_name();
  }
};
...
  SavePlacemarks(GetKmlFileRootFeature(argv[1]), &placemark_vector);
  sort(placemark_vector.begin(), placemark_vector.end(), ComparePlacemarks());
  for (size_t i = 0; i < placemark_vector.size(); ++i) {
    cout << i << " " << placemark_vector[i]->get_id() << " " <<
      placemark_vector[i]->get_name() << endl;
  }

```

# Example programs #

The libkml system comes with a small suite of
[example programs](http://libkml.googlecode.com/svn/trunk/examples/) to help you
get started. First build and install libkml as described above.

# Quick reference #

The libkml system consists of:

  * KML Base
  * KML DOM
  * KML Engine
  * KML Convenience
  * KML Regionator

The KML base library is internal to the libkml system.  There is no public API
to this module, but this must be linked with any use of libkml.

The KML DOM is the API to KML data which is a direct representation of the XML.
Everything you can
do in XML you can do in the DOM API.  KML DOM requires KML Base.

The KML Engine is the API to KML algorithms such as semantics and behavior
specified by the KML standard beyond the basic XML file format.
KML Engine requires KML DOM and KML Base.

The KML Convenience library consists of useful and common
utility code not directly part of the KML standard.  KML Convenience
requires KML Engine, KML DOM and KML Base.

The KML Regionator library consists of code useful for creating
Region-based NetworkLink hierarchies.  KML Regionator depends
on KML Convenience, KML Engine, KML DOM, and KML Base.

# KML DOM #

All classes and functions in the KML DOM are in the kmldom namespace.
Use "kml/dom.h" in your code and link with libkmldom.

## KML 2.2 ##

The libkml DOM implements standard OGC KML 2.2. Google's
[KML documentation](http://code.google.com/apis/kml/documentation/) is useful
for tutorials, examples, and reference material.

## Creating complex elements ##

Each complex element in KML 2.2 has a C++ type whose name is the same as the
element. For example, 

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

The KML DOM provides "smart pointer" memory management.  As such the factory
returns a "smart pointer" to the created Element and there is a typedef for
each pointer to each complex type in the language.  While this is a value type
it is actually still the same size as a regular pointer and is also used as a
pointer.

The "smart pointer" maintains a reference on your behalf to an Element while
the pointer remains in scope.  Passing the Element to set it as a child of
another Element gives the parent element a reference.  The reference count
decreases when either the parent is deleted or when your smart pointer goes out
of scope.  When the last reference to an element is release the storage is freed.

To help enforce the tree nature of XML no Element can be set to more than one
parent.   That is, a given Placemark can be added at most once to a given
Folder and never to a 2nd Folder.

Once an element is set to a given parent, it cannot be detached.

The `clear_xxx()` method both removes the child from the parent and releases
its reference to the underlying storage.

The "smart pointer" scheme is compatible with SWIG and as such no particular
memory management operations are required as is traditional in languages such
as Python and Java.

At present the "smart pointer" is simply a standard Boost intrusive\_ptr however
this is not directly considered part of the API.  We strongly encourage use of
the typedefs.

## Setting simple elements ##

Each simple element in KML 2.2 is a field in a complex element. The library
provides accessor functions to set, get, clear, and discover the existence of a
given simple element.

For example, any Feature (such as Placemark) has a 

&lt;name&gt;

 that can be manipulated with these methods:

```
const std::string& get_name() const;
bool has_name() const;
void set_name(const std::string& value);
void clear_name();
```

Note that the getter is always `const`.

The `has_xxx()` method returns true if this element was present in the parsed
KML or if it was previously set using `set_xxx()`.

The `clear_xxx()` method removes any value set either by the parser or by the
`set_xxx()` method. On serialization, no element is emitted for an element that
has been cleared.

The getter always returns a value, irrespective of the state returned by
`has_xxx()`. If `has_xxx()` is false, then the getter returns the default for
this element, as specifed in the KML Reference.

Simple elements are of either `std::string`, `double`, `int`, `boolean` or
`enum` type.

Here is how to access the 

&lt;description&gt;

 element:

```
const std::string& get_description() const;
bool has_description() const;
void set_description(const std::string& value);
void clear_description();
```

Here is how to access the 

&lt;north&gt;

 element:

```
double get_north() const;
void set_north(double north);
bool has_north() const;
void set_north(bool north);
```

Here is how to access the 

&lt;drawOrder&gt;

 element. Note that the name of the
element in the accessor method is folded to all lower case:

```
int get_draworder() const;
void set_draworder(bool draworder);
bool has_draworder() const;
void clear_draworder();
```

Here is how to access the 

&lt;visibility&gt;

 element:

```
bool get_visibility() const;
void set_visibility(bool visibility);
bool has_visibility() const;
void clear_visibility();
```

Here is how to access the 

&lt;altitudeMode&gt;

 element:

```
int get_altitudemode() const;
void set_altitudemode(int altitudemode);
bool has_altitudemode() const;
void clear_altitudemode();
```

## Enumerated value elements ##

Every enumerated value element has a C++ `enum`. For example, here is the
`enum` for 

&lt;altitudeMode&gt;

:

```
typedef enum {
  ALTITUDEMODE_CLAMPTOGROUND = 0,
  ALTITUDEMODE_RELATIVETOGROUND,
  ALTITUDEMODE_ABSOLUTE
} AltitudeModeEnum;
```

The `enum` type name is the element name with a leading capital and the string
'Enum' appended to it. Thus 

&lt;colorMode&gt;

 is of ColorModeEnum, and


&lt;listItemType&gt;

 is ListItemTypeEnum.

## More on complex elements ##

There are 3 kinds of complex child accessors: 1) single value of a specific
type, 2) single value of a group type, and 3) an array value of either a
specific or group type. Here are examples of each.

The 

&lt;LatLonBox&gt;

 child of 

&lt;GroundOverlay&gt;

 is an example of a complex child of a
specific type:

```
const LatLonBoxPtr& get_latlonbox() const;
void set_latlonbox(const LatLonBoxPtr& latlonbox);
bool has_latlonbox() const;
void clear_latlonbox();
```

The AbstractView child of Feature is an example of a complex child of a group
type. Both 

&lt;LookAt&gt;

 and 

&lt;Camera&gt;

 can be used with these accessors.

```
const AbstractViewPtr& get_abstractview() const;
void set_abstractview(const AbstractViewPtr& abstractview);
bool has_abstractview() const;
void clear_abstractview();
```

The Feature child of 

&lt;Folder&gt;

 is an example of an array value of a group type:

```
void add_feature(const FeaturePtr& feature);
size_t get_feature_array_size() const;
const kmldom::FeaturePtr& get_feature_array_at(unsigned int index) const;
```

(Note that in KML 2.2 the following elements are all of Feature type:
Placemark, NetworkLink, GroundOverlay, ScreenOverlay, PhotoOverlay, Folder,
and Document)

## Type inspection and conversion ##

All complex elements are derived from `kmldom::Element`. There is a type
conversion and an inspection function for each complex type. The libkml system
is not built with run-time type information (RTTI), hence `dynamic_cast` is not
used. If the element is of the desired type, then a pointer of that type is
returned, else NULL.

For example, the following code accesses the Geometry of a Placemark to
discover if it is a Point:

```
const kmldom::PlacemarkPtr placemark;
...
if (placemark->has_geometry()) {
  if (const kmldom::PointPtr point =
    kmldom::AsPoint(placemark->get_geometry()) {
    // Yes, it is a Point... see if it has coordinates:
    if (point->has_coordinates()) {
      ...
    }
  }
}
```

Every element has a type id that can be accessed with the Type() method:

```
const FeaturePtr feature = kml->get_feature();
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

## ParserObserver ##

New in 0.3 is an interface for providing SAX-style callbacks during parse.

```
class kmldom::ParserObserver {  
  // Called after this element is created by the parser.
  virtual bool NewElement(const ElementPtr& element) {
    return true;  // Default implementation is a NOP: parse continues.
  }

  // Called after the given child has been set to the given parent.
  virtual bool AddChild(const ElementPtr& parent, const ElementPtr& child) {
    return true;  // Default implementation is a NOP: parse continues.
  }
};
```

Use your ParserObserver with the new kmldom::Parser class like this:

Your ParserObserver specialization implements one or both of the
NewElement() and AddChild() methods.  You can return false from
either method to completely halt the parse at any time.  Always return
true if you wish the parse to completely finish.

```
MyParserObserver : public kmldom::ParserObserver {
  virtual bool NewElement(const kmldom::ElementPtr& element) {
    ...what ever you want..
    return true;  // or false if you want to terminate the parse
  };
  virtual bool AddChild(const ElementPtr& parent, const ElementPtr& child) {
    ...whatever you want...
    return true;
  };
};
```

Instantiate your ParserObserver:

```
MyParserObserver my_parser_observer;
```

Create a Parser and run it:

```
kmldom::Parser parser;
parser.AddObserver(&my_parser_observer);
kmldom::ElementPtr root = parser.Parse(kml_data, &errors);
```

Your ParserObserver is called as the parse proceeds and
a full DOM hierarchy is constructed as normal.

See the
[countkml.cc](http://code.google.com/p/libkml/source/browse/trunk/examples/helloworld/countkml.cc)
and
[checklinks.cc](http://code.google.com/p/libkml/source/browse/trunk/examples/helloworld/checklinks.cc)
examples for how this may be used.

The KML DOM fully constructed assuming no ParserObserver method
terminated the parse.

The kmlengine::ObjectIdParserObserver uses this to flag duplicate ids during parse within kmlengine::KmlFile.
The kmlengine::SharedStyleParserObserver uses this to gather shared styles in a KML file.
More on kmlengine::KmlFile below.

# KML Engine #

All classes and functions in the KML Engine are within the kmlengine namespace.
Use the "kml/engine.h" header and link with libkmlengine.

Here is an overview of the KML Engine functions and classes:

  * Bbox - class to manage bounding boxes
  * Clone - function to deep copy Elements
  * FeatureVisitor - walk the Feature hierarchy in a KML file
  * Find - find elements of a given type
  * GetLinks - get the links in a KML file
  * Href - parse the contents of 

&lt;href&gt;


  * KmlFile - Object ID and shared style support
  * KmzFile - KMZ read/write
  * Location - find the location of a Feature
  * Merge - merge one Element into another
  * Style resolution - every Feature has a resolved Style

## Bounding box ##

```
Bbox bbox;
bbox.ExpandLatLon(lat, lon);  // 0 or more times for a set of lat,lon.

// Inquire some things about the bounding box:
double mid_lat, mid_lon;
bbox.GetCenter(&mid_lat, &mid_lon);
double north = bbox.get_north()  // Same for s,e,w
bool contains = bbox.Contains(lat, lon);
```

## Element clone ##

Any Element can be deep-copied using kmlengine::Clone().
The newly created Element is a complete copy of all simple element
and complex element children of the original.  Just as one would
"copy-paste" the XML within a file to exactly duplicate an element,
kmlengine::Clone() provides such functionality within libkml.

```
kmldom::ElementPtr element;
kmldom::ElementPtr deep_copy = kmlengine::Clone(element);
```

## Feature support ##

A KML file is a hierarchy of Features.   Thus there is (possibly) a "root"
Feature.  (As with all things KML this is optional.  For example, a KML file
may have only a NetworkLinkControl or even be a "null" 

&lt;kml/&gt;

 element).

```
kmldom::Element root = kmldom::Parse(kmldata, NULL);
klmdom::FeaturePtr feature = kmlengine::GetRootFeature(root);
```

The VisitFeatureHierachy() function makes a depth-first walk of all Features
rooted at the given feature.  The feature can be the "root" Feature of a KML
file or any other Feature within.

```
class YourFeatureVisitor : public kmlengine::FeatureVisitor {
 public:
  virtual void VisitFeature(const kmldom::FeaturePtr& feature) {
    // ...your per-feature code...
  }
};
YourFeatureVisitor your_feature_visitor;
kmldom::FeaturePtr feature;
kmlengine::VisitFeatureHierarchy(feature, your_feature_visitor);
```

## Finding Elements ##

It is possible to get a flat list (in depth-first order) of all Elements of a
given type.  For example, find all the Placemarks in a KML file.

```
kmldom::ElementPtr element;
element_vector_t placemarks;
kmlengine::GetElementsById(element, kmldom::Type_Placemark, &placemarks);
```

## Finding links ##

A KML file may have 0 or more of many types of links such as
NetworkLink/Link/href, styleUrl, IconStyle/Icon/href, etc.  This function
finds them all.

```
href_vector_t hrefs;
GetLinks(kml_data, *hrefs);
```

## Href parsing ##

The content of any link element such as 

&lt;href&gt;

 can be parsed into
its scheme:://net\_loc/path#fragment using this:

```
// For example:
// <Link>
//   <href>http://example.com/cool/stuff.kml#object-id</href>
// </Link>
Href href(link->get_href());
const std::string scheme = href.get_scheme();  // "http"
const std::string net_loc = href.get_net_loc();  // "example.com"
const std::string path = href.get_path();  // "cool/stuff.kml"
const std::string fragment = href.get_fragment();  // "object-id"
```

## KML File ##

A KML file is the domain of id space as for any XML file.  (We use the term
"file" instead of "document" to not confuse with the KML 

&lt;Document&gt;

 element.
Note that a given KML file may have 0, 1 or many 

&lt;Document&gt;

 elements and that


&lt;Document&gt;

 is not necessarily the root Feature of a KML file).

A KML file also has an encoding and default namespace (and someday a set of
pairs of namespace prefixes and namespaces).

The KmlFile class provides a parse method and efficient object and shared style
lookup methods.

```
kmlengine::KmlFile kml_file;
kmldom::ElementPtr root = kml_file.ParseFromString(kmldata, &errors);
kmldom::ObjectPtr object = kml_file.GetObjectById(id);
kmldom::StyleSelectorPtr shared_style = kml_file.GetSharedStyleById(id);
```

Note that KmlFile's parser will reject the KML if there are duplicate ids.

(Future revisions of KmlFile in are expected to enhance this class as the main
parser and serializer of most common KML applications.  Future revisions are
anticipated to support unique object id management.  The kmldom parse and
serializer are expected to remain available for those applications with special
needs).

## KMZ File ##

The KmzFile class allows for reading and writing of KMZ files and provides some
useful utility functions. Historically, Google Earth has always read the
"default KML file" from a loaded KMZ file. The KmzFile class now defines
what is meant by "default KML file".

Some example code to illustrate use:

```
// We have just read the contents of a file into a string called file_data. We
// believe it to be a KMZ and would like to:
// - ensure it really is a KMZ file
// - read the default KML file from the archive
// - get a list of all files contained within the archive
// - read a file called "images/pic.jpg" from the archive

std::string kml;
// Ensure that the file is really a KMZ file.
if (!KmzFile::IsKmz(file_data)) {
  // Handle error.
}
// Instantiate the KmzFile object.
kmlengine::KmzFile* kmz_file = kmlengine::KmzFile::OpenFromString(file_data);
if (!kmz_file) {
  // Handle error.
}
if (!kmz_file->ReadKml(&kml)) {
  // Handle error.
}
// `kml` is now a string filled with the raw XML for the default KML file.
// We'll read the names of the archived files into a vector.
std::vector<std::string> list;
kmz_file_->List(&list);
// Now read "images/pic.jpg".
std::string pic_data;;
if (!kmz_file_->ReadFile("images/pic", &pice_data)) {
  // Handle error.
}
// Now delete the KmzFile instance when we're done with it.
// There's a handy scoped_ptr in third_party you could use instead.
delete kmz_file;
```

## Finding Feature and Geometry location ##

Any Feature may have a location.

```
double lat, lon;
if (kmlengine::GetFeatureLatLon(feature, &lat, &lon)) {
  ... yup, it has a location...
}
```

## Element merge ##

The simple element children of an Element maybe be merged
into those in another Element.

```
kmldom::ElementPtr some_new_values;
kmldom::ElementPtr override_me;
kmlengine::MergeFields(some_new_values, override_me);
```

Two Elements may be merged together.
This does a deep merge including all simple elements and
recursing on all complex elements.

```
kmldom::ElementPtr inline_style;
kmldom::ElementPtr shared_style;
kmlengine::MergeElements(inline_style, shared_style);
```

## Style resolution ##

Every Feature has a resolved Style. CreateResolvedStyle() creates a 

&lt;Style&gt;

,
based on resolving the styleUrl and inline StyleSelector of the given Feature.
The StyleStateEnum argument is used to indicate which state of any StyleMaps
to resolve.

Note that this requires use of KmlFile to parse the KML file.

```
kmlengine::KmlFile kml_file;
kmldom::FeaturePtr feature;
kmldom::StylePtr style = kmlengine::CreateResolvedStyle(feature, kml_file, normal or highlight);
```

# KML Convenience #

The KML Convenience classes and functions are in the kmlconvenience namespace.

These classes and functions are common and useful utilities not core to the
KML standard.

## Create commonly used elements ##

```
kmldom::PlacemarkPtr placemark = CreatePointPlacemark("My place", 38.38, -120.12);
```

This creates:

```
<Placemark>
  <name>My place</name>
  <Point>
    <coordinates>-120.12, 38.38</coordinates>
  </Point>
</Placemark>
```

## Feature list ##

The FeatureList class provides an efficient container to
operate on a set of Features including bounding box computation,
splitting by bounding box, sorting on score and saving
to a Container.

Put a bunch of Features in the FeatureList and sort on score.
(KML itself has no concept of Feature "score".  This is particular
to kmlconvenience::FeatureList.  The standard 

&lt;ExtendedData&gt;



&lt;Data&gt;


elements are used to hold the score.)

```
kmlconvenience::FeatureList feature_list;
for each feature:
  kmlconvenience::SetFeatureScore(the_features_score, feature);
  feature_list.PushBack(feature);
feature_list.Sort()
```

Split out the first N features within the given bounding box.

```
kmlconvenience::FeatureList features_in_some_bbox;
kmlengine::Bbox some_bbox;
feature_list.BboxSplit(bbox, how_many, &features_in_some_bbox);
```

Put the split out Features in a 

&lt;Folder&gt;

 and set the 

&lt;Region&gt;

 from
the bounding box.

```
kmldom::FolderPtr folder = factory->CreateFolder();
features_in_some_bbox.Save(folder);
kmldom::RegionPtr region = create-from-bbox(features_in_some_bbox);
folder->set_region(region);
```

## CSV file ##

The CsvFile class parses a "CSV" file of this format:

score|lat|lon|name|description[|style\_url]

A Point Placemark is created for each CSV entry.  CsvFile stores its result
into a FeatureList.

```
kmlconvenience::FeatureList feature_list;
kmlconvenience::CsvFile csv_file(&feature_list);
csv_file.ParseCsvFile("input.csv");
```

# KML Regionator #

The KML Regionator library creates Region-based NetworkLink KML
hierarchies.

The
[csvregionator.cc](http://code.google.com/p/libkml/source/browse/trunk/examples/regionator/csvregionator.cc)
example shows how this library is used to create
a Region-based NetworkLink KML hierarchy from a CSV file.

## RegionHander ##

This abstract class defines the interface which the Regionator algorithm
uses to walk a Region-hierarchy.

```
class kmlregionator::RegionHandler {
 public:
  // This method is the first one called for a given Region.  The implementation
  // of this method should return true if there is data in this Region and/or
  // below this Region.  The implementation must eventually return false
  // for the Region walk to complete.  This method is called _before_ all
  // children are visited.
  virtual bool HasData(const kmldom::RegionPtr& region) = 0;

  // This method is always called if the HasData() method returned true.
  // The implementation of this method should return the Feature for this
  // Region.  This method is called _after_ all children are visited.
  virtual kmldom::FeaturePtr GetFeature(const kmldom::RegionPtr& region) = 0;

  // This method is called for each Region with the KML data for a given
  // Region along with the file name that the parent NetworkLink will use
  // to fetch the file.  It is implementation dependent just how the KML
  // is saved, but the exact name in the filename argument should be used
  // with no modification.
  virtual void SaveKml(const kmldom::KmlPtr& kml,
                       const std::string& filename) = 0;
};
```

## Regionator ##

This class is the API to the "regionator" algorithm.

```
// Create a specific RegionHandler:
class MyRegionHandler : public kmlregionator::RegionHandler {...};
MyRegionHandler my_region_handler;
// The Regionator walks down the Region hierarchy starting at the
// specified Region calling the RegionHandler methods for each child
// Region in the hierarchy.  It is up to the HasData() method to
// eventually terminate the walk of the Region hierarchy.
kmldom::RegionPtr root_region;
kmlregionator::Regionator regionator(&my_region_handler, root_region);
regionator.Regionate();
// All "regionated" KML is now available wherever MyRegionHandler
// saved each file passed in to SaveKml().
```

## FeatureListRegionHandler ##

This is a RegionHandler for use with kmlconvenience::FeatureList.

Create a FeatureList of Point Placemarks from a CSV file:

```
kmlconvenience::FeatureList feature_list;
kmlconvenience::CsvFile csv_file;
csv_file.ParseCsvFile("input.csv");
```

Create a FeatureListRegionHandler for this FeatureList:

```
kmlregionator::FeatureListRegionHandler feature_list_region_handler(&feature_list);
```

Create a Region based on the FeatureList's bounding box:

```
Bbox bbox;
feature_list.ComputeBoundingBox(&bbox);
RegionPtr root = kmlconvenience::CreateRegion2d(
    bbox.get_north(),                                                                                        
    bbox.get_south(),                                                                                          
    bbox.get_east(),                                                                                           
    bbox.get_west(),                                                                                               
    256, -1);
```

Walk the Region hierarchy generating KML files:

```
kmlregionator::Regionator regionator(feature_list_region_handler, root);
regionator.Regionate();
```

NOTE: this is the mainline of the
[csvregionator.cc](http://code.google.com/p/libkml/source/browse/trunk/examples/regionator/csvregionator.cc)
example program.

# Future development #

With this 0.3 release we consider the API to the kmldom namespace quite stable.
Future development will be on further expansion of the KML Engine
and Convenience libraries built on the KML DOM.

  * more complete kmz read and write
  * more object id management
  * xml namespace support
  * balloon template expansion
  * networklink fetching
  * feature and geometry bounding box and lookat/camera computation
  * region visibility computation
  * NetworkLinkControl/Update processing

# Found a bug? #

You can file a bug using this project's
[issue tracker](http://code.google.com/p/libkml/issues/list). Please follow
basic [http://www.google.com/search?q=bug+reporting+guidelines bug reporting
procedure] and provide as much information as possible.