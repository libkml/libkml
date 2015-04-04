#summary libkml dom reference

# KML DOM #

All classes and functions in the KML DOM are in the kmldom namespace.
Use "kml/dom.h" in your code and link with libkmldom.

## KML 2.2 ##

The libkml DOM implements standard OGC KML 2.2. Google's
[KML documentation](http://code.google.com/apis/kml/documentation/) is useful
for tutorials, examples, and reference material.

## Creating complex elements ##

Each complex element in KML 2.2 has a C++ type whose name is the same as the
element. For example, `<Placemark>` is kmldom::PlacemarkPtr,
and `<GroundOverlay>` is kmldom::GroundOverlayPtr.

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

Once an element is set to a given parent, it cannot be detached using
a pure dom-level call.  At engine-level use `<Update>`/`<Delete>` to remove
a Feature from a Container.

The `clear_xxx()` method both removes the child from the parent and releases
its reference to the underlying storage.

The "smart pointer" scheme is compatible with SWIG and as such no particular
memory management operations are required as is traditional in languages such
as Python and Java.

At present the "smart pointer" is simply a standard Boost intrusive\_ptr however
this is not directly considered part of the API.  We strongly encourage use of
the typedefs as this helps protect your code from any future changes to
this specific means of memory management.

## Setting simple elements ##

Each simple element in KML 2.2 is a field in a complex element. The library
provides accessor functions to set, get, clear, and discover the existence of a
given simple element.

For example, any Feature (such as Placemark) has a `<name>` that can be
manipulated with these methods:

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

Here is how to access the `<description>` element:

```
const std::string& get_description() const;
bool has_description() const;
void set_description(const std::string& value);
void clear_description();
```

Here is how to access the `<north>` element:

```
double get_north() const;
void set_north(double north);
bool has_north() const;
void set_north(bool north);
```

Here is how to access the `<drawOrder>` element. Note that the name of the
element in the accessor method is folded to all lower case:

```
int get_draworder() const;
void set_draworder(bool draworder);
bool has_draworder() const;
void clear_draworder();
```

Here is how to access the ```<visibility>`` element:

```
bool get_visibility() const;
void set_visibility(bool visibility);
bool has_visibility() const;
void clear_visibility();
```

Here is how to access the `<altitudeMode>` element:

```
int get_altitudemode() const;
void set_altitudemode(int altitudemode);
bool has_altitudemode() const;
void clear_altitudemode();
```

## Enumerated value elements ##

Every enumerated value element has a C++ `enum`. For example, here is the
`enum` for `<altitudeMode>`:

```
typedef enum {
  ALTITUDEMODE_CLAMPTOGROUND = 0,
  ALTITUDEMODE_RELATIVETOGROUND,
  ALTITUDEMODE_ABSOLUTE
} AltitudeModeEnum;
```

The `enum` type name is the element name with a leading capital and the string
'Enum' appended to it. Thus `<colorMode>` is of ColorModeEnum, and
`<listItemType>` is ListItemTypeEnum.

## More on complex elements ##

There are 3 kinds of complex child accessors: 1) single value of a specific
type, 2) single value of a group type, and 3) an array value of either a
specific or group type. Here are examples of each.

The `<LatLonBox>` child of `<GroundOverlay>` is an example of a complex child of a
specific type:

```
const LatLonBoxPtr& get_latlonbox() const;
void set_latlonbox(const LatLonBoxPtr& latlonbox);
bool has_latlonbox() const;
void clear_latlonbox();
```

The AbstractView child of Feature is an example of a complex child of a group
type. Both `<LookAt>` and `<Camera>` can be used with these accessors.

```
const AbstractViewPtr& get_abstractview() const;
void set_abstractview(const AbstractViewPtr& abstractview);
bool has_abstractview() const;
void clear_abstractview();
```

The Feature child of `<Folder>` is an example of an array value of a group type:

```
void add_feature(const FeaturePtr& feature);
size_t get_feature_array_size() const;
const kmldom::FeaturePtr& get_feature_array_at(unsigned int index) const;
```

(Note that in KML 2.2 the following elements are all of Feature type:
Placemark, NetworkLink, GroundOverlay, ScreenOverlay, PhotoOverlay, Folder,
and Document.  Also in the Google KML extensions gx:Tour is a Feature.)

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
    kmldom::AsPoint(placemark->get_geometry())) {
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

```
class kmldom::ParserObserver {  
  // Called after this element is created by the parser.
  virtual bool NewElement(const ElementPtr& element) {
    return true;  // Default implementation is a NOP: parse continues.
  }

  // Called after child is fully constructed before it is added to the parent.
  // A derived class can return false to inhibit adding the child to the parent.
  // Returning true permits the parser to add this child to the parent.
  virtual bool EndElement(const ElementPtr& parent, const ElementPtr& child) {
    return true;
  }

  // Called after the given child has been set to the given parent.
  virtual bool AddChild(const ElementPtr& parent, const ElementPtr& child) {
    return true;  // Default implementation is a NOP: parse continues.
  }
};
```

Use your ParserObserver with the kmldom::Parser class as follows.

Derive a class from ParserObserver and implement one or more of the
NewElement(), EndElement() and AddChild() methods.

```
MyParserObserver : public kmldom::ParserObserver {
  virtual bool NewElement(const kmldom::ElementPtr& element) {
    ...what ever you want..
    return true;  // or false if you want to terminate the parse
  };
  // EndElement() not implemented in derived class so default is used.
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
[countkml.cc](http://code.google.com/p/libkml/source/browse/trunk/examples/helloworld/countkml.cc),
[checklinks.cc](http://code.google.com/p/libkml/source/browse/trunk/examples/helloworld/checklinks.cc)
and
[streamkml.cc](http://code.google.com/p/libkml/source/browse/trunk/examples/engine/streamkml.cc)
examples for how this may be used.

The KML DOM fully constructed assuming no ParserObserver method
terminated the parse or inhibited parenting of a child to a parent.

The kmlengine::ObjectIdParserObserver uses this to flag duplicate ids during
parse within kmlengine::KmlFile.
The kmlengine::SharedStyleParserObserver uses this to gather shared styles
in a KML file.
See
[kmlengine::!KmlFile](http://code.google.com/p/libkml/wiki/KmlEngineReference)
for more information.