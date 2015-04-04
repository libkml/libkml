#summary libkml quick start

Here is a quick start to programming with libkml.

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