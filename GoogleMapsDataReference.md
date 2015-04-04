#summary libkml google maps data reference

# GoogleMapsData and HttpClient #

The GoogleMapsData class provides a C++ API to the Google Maps Data API.
This document provides an overview of the functionality of this API.

There are two main components: the
[GoogleMapsData](http://code.google.com/p/libkml/source/browse/trunk/src/kml/convenience/google_maps_data.h)
class and a class you supply derived from the
[HttpClient](http://code.google.com/p/libkml/source/browse/trunk/src/kml/convenience/http_client.h) class.

For the most part the GoogleMapsData methods package up HTTP POST
and GET requests, thus this class is part of the convenience methods
of libkml.  There are two kinds of data passed over HTTP: Atom
and media where media is CSV or KML all of which are supported in libkml.

See the
[Google Maps Data API HTTP Protocol Guide](http://code.google.com/apis/maps/documentation/mapsdata/developers_guide_protocol.html) for the details of the HTTP protocol.

In addition to the Google Maps Data API there are also classes in libkml with
limited support for
[Google Documents List Data API](http://code.google.com/apis/documents/overview.html),
[Google Spreadsheets Data API](http://code.google.com/apis/spreadsheets/data/3.0/developers_guide.html), and
[Google PicasaWeb API](http://code.google.com/apis/picasaweb/overview.html)
in the
[GoogleDocList](http://code.google.com/p/libkml/source/browse/trunk/src/kml/convenience/google_doc_list.h),
[GoogleSpreadsheets](http://code.google.com/p/libkml/source/browse/trunk/src/kml/convenience/google_spreadsheets.h), and
[GooglePicasaWeb](http://code.google.com/p/libkml/source/browse/trunk/src/kml/convenience/google_picasa_web.h) classes respectively.

## HttpClient ##

A GoogleMapsData instance requires a HttpClient to perform communications.

```
class YourHttpClient : public kmlconvenience::HttpClient {
 public:
  virtual bool SendRequest(...) const {
    ...your network I/O code goes here...
  }
};
```

An HttpClient must be logged in to the appropriate service.
Here is an example of an HttpClient logged in to the Google Maps Data API:

```
YourHttpClient* your_http_client = new YourHttpClient("your-app-name");
const string& maps_data = GoogleMapsData::get_service_name();
string user_name = [prompt user]
string password = [prompt user]
your_http_client->Login(maps_data, user_name, password);
```

See
[CurlHttpFetch](http://code.google.com/p/libkml/source/browse/trunk/examples/hellonet/curlfetch.h)
for an HttpClient using [libcurl](http://curl.haxx.se/libcurl/).
libcurl is not provided with libkml but it is
available for most any platform.

## GoogleMapsData ##

The GoogleMapsData::Create static method creates a GoogleMapsData object
using the created and logged-in HttpClient:

```
GoogleMapsData* maps_data = GoogleMapsData::Create(your_http_client);
```

The GetMetaFeed() method fetches and parses the Atom feed of the list of
the user's maps:

```
kmldom::AtomFeedPtr meta_feed = maps_data->GetMetaFeed();
```

The Atom `entry and `feed` elements are supported by libkml:

```
for (size_t e = 0; e < meta_feed->get_entry_array_size(); ++e) {
  const kmldom::AtomEntryPtr& entry = meta_feed->get_entry_array_at(e);
  std::cout << "[title] " << entry->get_title() << std::endl;
}
```

The are additional methods on GoogleMapsData to:
  * Create a new map
  * Add KML Features to a map
  * Get KML Features in a map

See [google\_maps\_data.h](http://code.google.com/p/libkml/source/browse/trunk/src/kml/convenience/google_maps_data.h) for details.

## Google Maps Data spatial query support ##

The
[GetSearchFeed](http://code.google.com/p/libkml/source/browse/trunk/src/kml/convenience/google_maps_data.h)
method essentially returns the feature of a map within a given area.

```
string atom_feed;
google_maps_data->GetSearchFeed(search_feed_uri, search_parameters, atom_feed);
```

## Google Maps Data media support ##

In addition to Atom-based HTTP POST and GET the Google Maps Data API
supports raw media-based HTTP POST as well.

The [PostCsv](http://code.google.com/p/libkml/source/browse/trunk/src/kml/convenience/google_maps_data.h) method creates a new map and adds to it a feature
from each line in a CSV file.

```
// You'll be reading your CSV from a big file no doubt, but here is
// a very simple CSV.  First line is the "schema", each subsequent line is
// a <Point> <Placemark>.  Note how an item with a common is quoted.
string csv_data = "name,latitude,longitude,description\n"
                  "Hello,-11.968312,-77.066395,"Welcome to Lima,Peru!"\n";

// This does exactly one HTTP POST.  Your code will check for errors.
AtomEntryPtr entry = google_maps_data->PostCsv("Hello Lima", csv_data, NULL);

// Here's how to get the URL for the KML of your new map.
string kml_url;  // Put this in a <NetworkLink>, for example.
GoogleMapsData::GetKmlUri(entry, &kml_uri);
```

The [PostKml](http://code.google.com/p/libkml/source/browse/trunk/src/kml/convenience/google_maps_data.h) method creates a new map and adds to it a feature
from each `<Placemark>` in the KML file.  Note that this does not preserve
the KML file in full.  Think of the KML file as a means to transport
KML `<Placemark>`s to the Google Maps Data API.

```
// You'll be reading your KML from a big file no doubt, but here is
// a very simple KML file.
// a <Point> <Placemark>.
string kml_data = "<kml>"
                  "  <Placemark>"
                  "  <name>Hello</name>"
                  "  <description>Welcome to Lima,Peru!</description>"
                  "    <Point>"
                  "      <coordinates>-77.066395,-11.968312</coordinates>"
                  "    </Point>"
                  "  </Placemark>"
                  "</kml>";

// This does exactly one HTTP POST.  Your code will check for errors.
AtomEntryPtr entry = google_maps_data->PostKml("Hello Lima", kml_data);

// Here's how to get the URL of your new map.
string kml_url;
GoogleMapsData::GetKmlUri(entry, &kml_uri);
```

## Examples ##

There are many example command line programs using the GoogleMapsData and
other Google Data API classes:

  * [listgmaps.cc](http://code.google.com/p/libkml/source/browse/trunk/examples/hellonet/listgmaps.cc) - list your maps
  * [getgmapkml.cc](http://code.google.com/p/libkml/source/browse/trunk/examples/hellonet/getgmapkml.cc) - get the KML for a map
  * [uploadgmap.cc](http://code.google.com/p/libkml/source/browse/trunk/examples/hellonet/uploadgmap.cc) - upload KML using Atom
  * [uploadgmapcsv.cc](http://code.google.com/p/libkml/source/browse/trunk/examples/hellonet/uploadgmapcsv.cc) - create a new map from CSV
  * [uploadgmapkml.cc](http://code.google.com/p/libkml/source/browse/trunk/examples/hellonet/uploadgmapkml.cc) - create a new map from KML
  * [gsheet2gmap.cc](http://code.google.com/p/libkml/source/browse/trunk/examples/hellonet/gsheet2gmap.cc) - create a map from a Google Spreadsheet
  * [searchgmap.cc](http://code.google.com/p/libkml/source/browse/trunk/examples/hellonet/searchgmap.cc) - spatial search over a map