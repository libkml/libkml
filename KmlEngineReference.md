#summary libkml engine reference

# KML Engine #

All classes and functions in the KML Engine are within the kmlengine namespace.
Use the "kml/engine.h" header and link with libkmlengine.

The KmlFile class is the core component of the KML Engine.  Most typical usage
of libkml is expected to center on creation and use of KmlFile.  The KmlCache
class is the core component for networked KML; KmlCache creates a KmlFile
for any KML file it fetches.  Balloon expansion, style resolution, and Update processing
are based on KmlFile and KmlCache.

Here is an overview of the KML Engine functions and classes:

  * Bbox - class to manage bounding boxes
  * Clone - function to deep copy Elements
  * CreateBalloonText - this function creates a Feature's balloon content
  * FeatureView - compute LookAt for Feature
  * FeatureVisitor - walk the Feature hierarchy in a KML file
  * Find - find elements of a given type
  * FindXmlNamespaces - find XML namespaces used in an Element hierarchy
  * GetLinks - get the links in a KML file
  * KmlCache - KML networking
  * KmlFile - Object ID and shared style support
  * KmlStream - process a large KML file in a streamed fashion
  * KmlUri - URI parsing and resolution, KMZ aware URI handling
  * KmzCache - networked KMZ access
  * KmzFile - KMZ read/write
  * Link - process Link and Icon
  * Location - find the location of a Feature
  * Merge - merge one Element into another
  * Style inlining - parse KML and inline shared StyleSelectors
  * Style resolution - every Feature has a resolved Style
  * Style splitting - parse KML and split inline styles to be shared
  * Update processing

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

## Balloon content ##

Any Feature can have balloon content.  Use CreateBalloonText() to
build the balloon text as appropriate for its styleUrl and/or StyleSelector.

If the KmlFile is created using KmlCache the internals of
CreateBalloonText() will use the network-enabled functionality
of CreateResolvedStyle() to resolve and fetch any schemaUrls or styleUrls.

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
may have only a NetworkLinkControl or even be a "null" `<kml/>` element).

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

Note that KmlFile provides fast lookup of any element by XML id.
See the notes on KmlFile below for more information.

## Finding links ##

A KML file may have 0 or more of many types of links such as
NetworkLink/Link/href, styleUrl, IconStyle/Icon/href, etc.  This function
finds them all.

```
href_vector_t hrefs;
GetLinks(kml_data, *hrefs);
```

Note that KmlFile automatically gathers links.  See the notes on KmlFile below
for more information.

## KML Cache ##

The KmlCache class is a core component for networked KML.  You supply
your own network fetcher (the example programs show a simple example
based on curl).  You fetch KML (or KMZ) content via NetCache and that
NetCache and your network fetcher will be used from within the balloon
expansion and style resolution code to fetch remote shared styles and schemas.
Multiple references to the same styleUrl from different Features will
resolve to a single parsed KmlFile holding the StyleSelector.

A KmlFile created by KmlCache retains a pointer back to this KmlCache
which is used by the style resolution machinery to fetch any styleUrls
encountered.  The KML Engine does not directly to ANY network I/O.
Also, note that absolute file references in remotely fetched KML is
explicitely disallowed.  (Relative file references, of course, function
fine from KML loaded directly from the local file system).

A KmlFile created directly from KmlFile will not have a KmlCache to
use and any remote style or schema references will be quietly ignored.
(The default NetFetcher returns false for any URL).

```
class YourNetFetcher : public kmlbase::NetFetcher {
  virtual bool FetchUrl(const std::string& url, std::string* data) const {
    // You fetch the URL and save the result to data.
    return true;  // Assuming the fetch succeeded.
  }
};

YourNetFetcher your_net_fetcher;
kmlengine::KmlCache kml_cache(&your_net_fetcher, cache_size);
kmlengine::KmlFile kml_file = kml_cache.FetchKml("http://.../foo.kml");

std::string image_data;
bool status = kml_cache.FetchData("http://.../image.jpg", &image_data);

std::string balloon_text = CreateBalloonText(kml_file,
                                             some_feature_in_kml_file);
```

## KML File ##

The KmlFile is a central component to the KML Engine and in typical
applications should be used to parse a KML file.  Use NetCache to fetch
KML over the network and to associate a URL with a KmlFile.

A KML file is the domain of id space as for any XML file.  (We use the term
"file" instead of "document" to not confuse with the KML `<Document>` element.
Note that a given KML file may have 0, 1 or many `<Document>` elements and that
`<Document>` is not necessarily the root Feature of a KML file).

A KML file also has an encoding and default namespace (and someday a set of
pairs of namespace prefixes and namespaces).

The KmlFile class provides a parse method and efficient object and shared style
lookup methods.

```
std::string kmldata;
std::string errors;
kmlengine::KmlFilePtr kml_file = KmlFile::CreateFromParse(kmldata, &errors);
kmldom::ObjectPtr object = kml_file.GetObjectById(id);
kmldom::StyleSelectorPtr shared_style = kml_file.GetSharedStyleById(id);
```

Note that KmlFile's parser will reject the KML if there are duplicate ids.

A KmlFile can be constructed from a "raw" KML DOM.   The CreateFromImport
static method walks the DOM an saves a mapping for each Object with an id.
This method will fail on a DOM with duplicate ids.

```
kmldom::ElementPtr element = ...
kmlengine::KmlFile kml_file = KmlFile::CreateFromImport(element);
```

The links in a KmlFile are available using get\_link\_parent\_vector():

```
kmlengine::KmlFile* kml_file = KmlFile::Create*();
const ElementVector& link_parents = kml_file->get_link_parent_vector()
```

The serialize method on KmlFile adds an xml header and sets the
xmlns's on the root element as per the XML namespaces actually
found in the Element hierarchy.

```
std::string xml;
kml_file->SerializeToString(&xml);
```

## KML Stream ##

A KML stream provides streamed I/O and streamed processing of a
large KML file.

This builds a DOM from a file using streamed I/O:

```
std::ifstream input(...);  // Or any other std::istream.  
std::string errors;
KmlStream* kml_stream = KmlStream::ParseFromIstream(input, &errors, NULL);
ElementPtr root = kml_stream->get_root();
```

A large (or infinite) KML file can be processed on the fly using a
ParserObserver with KmlStream as follows:

```
std::ifstream input(...);
class YourParserObserver : public kmldom::ParserObserver {
 public:
  bool EndElement(const ElementPtr& parent, const ElementPtr& child) {
    // Your code here to example child about to be added to parent.
    // Return false to inhibit adding child to parent.
  }
};
YourParserObserver observer;
KmlStream* kml_stream = KmlStream::ParseFromIstream(input, NULL, &observer);
```

See examples/engine/streamkml.cc for a complete example.

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
kmz_file->List(&list);
// Now read "images/pic.jpg".
std::string pic_data;;
if (!kmz_file->ReadFile("images/pic.jpg", &pic_data)) {
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

Every Feature has a resolved Style. CreateResolvedStyle() creates a `<Style>`,
based on resolving the styleUrl and inline StyleSelector of the given Feature.
The StyleStateEnum argument is used to indicate which state of any StyleMaps
to resolve.

Note that this requires use of KmlFile to parse the KML file.

Networked style resolution (styleUrl's to remote KML/KMZ) is performed
via if the KmlFile was created from a fetch through KmlCache.

```
kmlengine::KmlFile kml_file;
kmldom::FeaturePtr feature;
kmldom::StylePtr style = kmlengine::CreateResolvedStyle(feature, kml_file, normal or highlight);
```

## Update ##

The ProcessUpdate function processes the given Update into the given KmlFile.
An Update is one or more of any number of Change, Create and Delete operations.

```
kmldom::UpdatePtr update;
kmlengine:KmlFilePtr kml_file;
kmlengine::ProcessUpdate(update, kml_file);
```

## URI Resolution ##

KMZ-aware URI resolution functions are available:

```
const std::string kml_url("http://host.com/path/file.kmz/dir/image.jpg");
std::string kmz_url;  // Will hold fetchable URL to KMZ file
std::string kmz_path;  // Will hold path inside KMZ archive.
bool is_kmz = kmlengine::KmzSplit(kml_url, &kmz_url, &kmz_path);
```

The ResolveUri() function can be used with any KML uri (including
those referencing into KMZ files) with the content of any href-like
field in a KML file.  The following is based KMZ-aware path name
splitting and then RFC 3986.

```
// The URL of the KML file:
const std::string base("http://host.com/foo.kml");
// From an <href> such as <NetworkLink>'s <Link>:
const std::string relative("dir/goo.kml");
std::string result;
bool ok = kmlengine::ResolveUri(base, relative, &result);
// result is now "http://host.com/dir/goo.kml".
```

See kml/engine/kml\_uri.h for more information.