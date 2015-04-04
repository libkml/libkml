#summary libkml convenience reference

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

## Feature list ##

The FeatureList class provides an efficient container to
operate on a set of Features including bounding box computation,
splitting by bounding box, sorting on score and saving
to a Container.

Put a bunch of Features in the FeatureList and sort on score.
(KML itself has no concept of Feature "score".  This is particular
to kmlconvenience::FeatureList.  The standard `<ExtendedData><Data>`
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

Put the split out Features in a `<Folder>` and set the `<Region>` from
the bounding box.

```
kmldom::FolderPtr folder = factory->CreateFolder();
features_in_some_bbox.Save(folder);
kmldom::RegionPtr region = create-from-bbox(features_in_some_bbox);
folder->set_region(region);
```
