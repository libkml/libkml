#summary libkml regionator reference

# KML Regionator #

The KML Regionator library creates Region-based NetworkLink KML
hierarchies.

The
[csvregionator.cc](http://code.google.com/p/libkml/source/browse/trunk/examples/regionator/csvregionator.cc)
example shows how this library is used to create
a Region-based NetworkLink KML hierarchy from a CSV file.

## RegionHandler ##

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