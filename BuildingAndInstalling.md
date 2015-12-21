# Building and Installing libkml #

Please read the DEPENDENCIES file carefully and ensure you have the correct
versions of all required software.

This is last updated for version 1.3.0. The build system has been changed to cmake!

## Building ##

We assume you have a cmake 2.8 or higher installed. 
Performing a basic build should be as simple as:

```
git clone https://github.com/libkml/libkml libkml-1.3.0
mkdir libkml-1.3.0.build ; cd libkml-1.3.0.build
cmake ../libkml-1.3.0
```
libkml requires some external libraries. They are listed below in a random order
* boost
* zlib
* minizip
* uriparser
If any of these are found missing, cmake will download and install it automatically!

### Testing (optional) ####
To Enable Testing, you need to pass additional options to your cmake configure step:
```
cd libkml-1.3.0.build
cmake -DBUILD_TESTING=TRUE ../libkml-1.3.0
```

### Examples (optional) ####
To Enable Examples, you need to pass additional options to your cmake configure step:
```
cd libkml-1.3.0.build
cmake -DBUILD_EXAMPLES=TRUE ../libkml-1.3.0
```
#### Build and install ####
```
make
sudo make install
```
### SWIG bindings ###

If you want to create bindings for the additional supported languages, you need
to install the Simplified Wrapper and Interface Generator
([SWIG](http://www.swig.org/)) version 1.3.35.

NOTE: This dependency is not auto-downloaded by cmake

Once SWIG is installed, you can re-run cmake. It will automatically detect swig. But they cmake options that enable bindings are not enabled even if swig is found. This change is made intentionally and not a bug. To activate bindings:
```
cd libkml-1.3.0.build
cmake -DWITH_SWIG=TRUE -DWITH_PYTHON=TRUE -DWITH_JAVA=TRUE ../libkml-1.3.0 
```
The Python bindings, if enabled will be installed to a site-packages directory. 
This will likely be similar to `/usr/local/lib/python2.7/site-packages/`. 
Your `PYTHONPATH` will of course have to know about this directory.


## Microsoft Windows ##
CMake is cross platform and works with a lot of generators. 
It is easy to generate Visual Studio project files using cmake. Check the CMAKE_GENERATOR variable when using cmake-gui.exe on windows. I had tested a build on VS2010. Other versions might work but the case is simply not tested.

# Running the unit tests #

It is HIGHLY recommended that you build and run all unit tests.
We consider the unit tests of libkml as important as the code itself
given these assert semantics about the KML language itself and not
just the libkml system.  You will note that the unit tests for a given
module often far exceed that module in raw lines of code.

## Build and run the libkml unit tests ##

We have provided a large suite of unit tests to verify the correct behavior of
libkml. We use the [GoogleTest framework](http://googletest.googlecode.com), which
on Linux and Mac OS X is built automatically as a part of the automake process and is
supplied in binary form for MS Windows.

you can run the tests via ctest no matter what platform you are!

```
ctest 
```

Excerpts of the test output looks as follows.

In reporting any problem with libkml please also submit a complete
trace of your run of the unit test suite.

```
Test project ~/projects/libkml-1.3.0.build
        Start   1: base_attributes
  1/130 Test   #1: base_attributes ..........................   Passed    0.00 sec
        Start   2: base_color32
  2/130 Test   #2: base_color32 .............................   Passed    0.00 sec
        Start   3: base_csv_splitter
  3/130 Test   #3: base_csv_splitter ........................   Passed    0.01 sec
        Start   4: base_date_time
  4/130 Test   #4: base_date_time ...........................   Passed    0.00 sec
        Start   5: base_expat_handler_ns
  5/130 Test   #5: base_expat_handler_ns ....................   Passed    0.00 sec
        Start   6: base_file
  6/130 Test   #6: base_file ................................   Passed    0.01 sec
        Start   7: base_math_util
  7/130 Test   #7: base_math_util ...........................   Passed    0.01 sec
        Start   8: base_referent
  8/130 Test   #8: base_referent ............................   Passed    0.01 sec
        Start   9: base_string_util
  9/130 Test   #9: base_string_util .........................   Passed    0.01 sec
        Start  10: base_tempfile
 10/130 Test  #10: base_tempfile ............................   Passed    0.01 sec
        Start  11: base_time_util
 11/130 Test  #11: base_time_util ...........................   Passed    0.01 sec
        Start  12: base_util
 12/130 Test  #12: base_util ................................   Passed    0.01 sec
        Start  13: base_vec3
 13/130 Test  #13: base_vec3 ................................   Passed    0.01 sec
        Start  14: base_version
 14/130 Test  #14: base_version .............................   Passed    0.01 sec
        Start  15: base_xml_element
 15/130 Test  #15: base_xml_element .........................   Passed    0.01 sec
        Start  16: base_xml_file
 16/130 Test  #16: base_xml_file ............................   Passed    0.01 sec
        Start  17: base_xml_namespaces
 17/130 Test  #17: base_xml_namespaces ......................   Passed    0.01 sec
        Start  18: base_xmlns
 18/130 Test  #18: base_xmlns ...............................   Passed    0.01 sec
        Start  19: base_net_cache
 19/130 Test  #19: base_net_cache ...........................   Passed    0.09 sec
        Start  20: base_uri_parser
 20/130 Test  #20: base_uri_parser ..........................   Passed    0.00 sec
        Start  21: base_zip_file
 21/130 Test  #21: base_zip_file ............................   Passed    1.31 sec
        Start  22: base_expat_parser
 22/130 Test  #22: base_expat_parser ........................   Passed    0.00 sec
        Start  23: regionator_csv_file
 23/130 Test  #23: regionator_csv_file ......................   Passed    0.01 sec
        Start  24: regionator_csv_parser
 24/130 Test  #24: regionator_csv_parser ....................   Passed    0.01 sec
        Start  25: regionator_element_counter
 25/130 Test  #25: regionator_element_counter ...............   Passed    0.01 sec
        Start  26: regionator_feature_list
 26/130 Test  #26: regionator_feature_list ..................   Passed    0.01 sec
        Start  27: regionator_google_doc_list
 27/130 Test  #27: regionator_google_doc_list ...............   Passed    0.01 sec
        Start  28: regionator_google_maps_data
 28/130 Test  #28: regionator_google_maps_data ..............   Passed    0.03 sec
        Start  29: regionator_google_picasa_web
 29/130 Test  #29: regionator_google_picasa_web .............   Passed    0.01 sec
        Start  30: regionator_google_spreadsheets
 30/130 Test  #30: regionator_google_spreadsheets ...........   Passed    0.04 sec
        Start  31: regionator_gpx_trk_pt_handler
 31/130 Test  #31: regionator_gpx_trk_pt_handler ............   Passed    0.05 sec
        Start  32: regionator_http_client
 32/130 Test  #32: regionator_http_client ...................   Passed    0.02 sec
        Start  33: regionator_kml_feature_list_saver
 33/130 Test  #33: regionator_kml_feature_list_saver ........   Passed    0.01 sec
        Start  34: regionator_kmz_check_links
 34/130 Test  #34: regionator_kmz_check_links ...............   Passed    0.15 sec
        Start  35: dom_abstractlatlonbox
 35/130 Test  #35: dom_abstractlatlonbox ....................   Passed    0.01 sec
        Start  36: dom_abstractview
 36/130 Test  #36: dom_abstractview .........................   Passed    0.02 sec
        Start  37: dom_atom
 37/130 Test  #37: dom_atom .................................   Passed    0.02 sec
        Start  38: dom_balloonstyle
 38/130 Test  #38: dom_balloonstyle .........................   Passed    0.01 sec
        Start  39: dom_colorstyle
 39/130 Test  #39: dom_colorstyle ...........................   Passed    0.01 sec
        Start  40: dom_container
 40/130 Test  #40: dom_container ............................   Passed    0.01 sec
        Start  41: dom_document
 41/130 Test  #41: dom_document .............................   Passed    0.01 sec
        Start  42: dom_element
 42/130 Test  #42: dom_element ..............................   Passed    0.01 sec
        Start  43: dom_extendeddata
 43/130 Test  #43: dom_extendeddata .........................   Passed    0.02 sec
        Start  44: dom_feature
 44/130 Test  #44: dom_feature ..............................   Passed    0.01 sec
        Start  45: dom_folder
 45/130 Test  #45: dom_folder ...............................   Passed    0.01 sec
        Start  46: dom_geometry
 46/130 Test  #46: dom_geometry .............................   Passed    0.03 sec
        Start  47: dom_hotspot
 47/130 Test  #47: dom_hotspot ..............................   Passed    0.01 sec
        Start  48: dom_iconstyle
 48/130 Test  #48: dom_iconstyle ............................   Passed    0.02 sec
        Start  49: dom_kml_cast
 49/130 Test  #49: dom_kml_cast .............................   Passed    0.08 sec
        Start  50: dom_kml
 50/130 Test  #50: dom_kml ..................................   Passed    0.01 sec
        Start  51: dom_kml_factory
 51/130 Test  #51: dom_kml_factory ..........................   Passed    0.01 sec
        Start  52: dom_kml22
 52/130 Test  #52: dom_kml22 ................................   Passed    0.01 sec
        Start  53: dom_labelstyle
 53/130 Test  #53: dom_labelstyle ...........................   Passed    0.02 sec
        Start  54: dom_linestyle
 54/130 Test  #54: dom_linestyle ............................   Passed    0.02 sec
        Start  55: dom_link
 55/130 Test  #55: dom_link .................................   Passed    0.03 sec
        Start  56: dom_liststyle
 56/130 Test  #56: dom_liststyle ............................   Passed    0.01 sec
        Start  57: dom_model
 57/130 Test  #57: dom_model ................................   Passed    0.01 sec
        Start  58: dom_networklink
 58/130 Test  #58: dom_networklink ..........................   Passed    0.01 sec
        Start  59: dom_networklinkcontrol
 59/130 Test  #59: dom_networklinkcontrol ...................   Passed    0.02 sec
        Start  60: dom_object
 60/130 Test  #60: dom_object ...............................   Passed    0.02 sec
        Start  61: dom_overlay
 61/130 Test  #61: dom_overlay ..............................   Passed    0.01 sec
        Start  62: dom_placemark
 62/130 Test  #62: dom_placemark ............................   Passed    0.01 sec
        Start  63: dom_polystyle
 63/130 Test  #63: dom_polystyle ............................   Passed    0.01 sec
        Start  64: dom_region
 64/130 Test  #64: dom_region ...............................   Passed    0.02 sec
        Start  65: dom_round_trip
 65/130 Test  #65: dom_round_trip ...........................   Passed    0.13 sec
        Start  66: dom_schema
 66/130 Test  #66: dom_schema ...............................   Passed    0.02 sec
        Start  67: dom_snippet
 67/130 Test  #67: dom_snippet ..............................   Passed    0.01 sec
        Start  68: dom_style
 68/130 Test  #68: dom_style ................................   Passed    0.01 sec
        Start  69: dom_stylemap
 69/130 Test  #69: dom_stylemap .............................   Passed    0.01 sec
        Start  70: dom_styleselector
 70/130 Test  #70: dom_styleselector ........................   Passed    0.02 sec
        Start  71: dom_substyle
 71/130 Test  #71: dom_substyle .............................   Passed    0.02 sec
        Start  72: dom_timeprimitive
 72/130 Test  #72: dom_timeprimitive ........................   Passed    0.01 sec
        Start  73: dom_vec2
 73/130 Test  #73: dom_vec2 .................................   Passed    0.01 sec
        Start  74: dom_unknown
 74/130 Test  #74: dom_unknown ..............................   Passed    0.01 sec
        Start  75: dom_kml_handler
 75/130 Test  #75: dom_kml_handler ..........................   Passed    0.06 sec
        Start  76: dom_kml_handler_ns
 76/130 Test  #76: dom_kml_handler_ns .......................   Passed    0.02 sec
        Start  77: dom_parser
 77/130 Test  #77: dom_parser ...............................   Passed    0.01 sec
        Start  78: dom_serializer
 78/130 Test  #78: dom_serializer ...........................   Passed    0.02 sec
        Start  79: dom_gx_timeprimitive
 79/130 Test  #79: dom_gx_timeprimitive .....................   Passed    0.02 sec
        Start  80: dom_gx_tour
 80/130 Test  #80: dom_gx_tour ..............................   Passed    0.01 sec
        Start  81: dom_xal
 81/130 Test  #81: dom_xal ..................................   Passed    0.08 sec
        Start  82: dom_xml_serializer
 82/130 Test  #82: dom_xml_serializer .......................   Passed    0.01 sec
        Start  83: dom_xsd
 83/130 Test  #83: dom_xsd ..................................   Passed    0.01 sec
        Start  84: dom_visitor
 84/130 Test  #84: dom_visitor ..............................   Passed    0.01 sec
        Start  85: dom_visitor_driver
 85/130 Test  #85: dom_visitor_driver .......................   Passed    0.02 sec
        Start  86: engine_bbox
 86/130 Test  #86: engine_bbox ..............................   Passed    0.01 sec
        Start  87: engine_clone
 87/130 Test  #87: engine_clone .............................   Passed    0.02 sec
        Start  88: engine_entity_mapper
 88/130 Test  #88: engine_entity_mapper .....................   Passed    0.02 sec
        Start  89: engine_feature_balloon
 89/130 Test  #89: engine_feature_balloon ...................   Passed    0.03 sec
        Start  90: engine_feature_visitor
 90/130 Test  #90: engine_feature_visitor ...................   Passed    0.01 sec
        Start  91: engine_feature_view
 91/130 Test  #91: engine_feature_view ......................   Passed    0.01 sec
        Start  92: engine_find
 92/130 Test  #92: engine_find ..............................   Passed    0.01 sec
        Start  93: engine_find_xml_namespaces
 93/130 Test  #93: engine_find_xml_namespaces ...............   Passed    0.01 sec
        Start  94: engine_get_link_parents
 94/130 Test  #94: engine_get_link_parents ..................   Passed    0.01 sec
        Start  95: engine_get_links
 95/130 Test  #95: engine_get_links .........................   Passed    0.01 sec
        Start  96: engine_href
 96/130 Test  #96: engine_href ..............................   Passed    0.02 sec
        Start  97: engine_id_mapper
 97/130 Test  #97: engine_id_mapper .........................   Passed    0.02 sec
        Start  98: engine_kmz_cache
 98/130 Test  #98: engine_kmz_cache .........................   Passed    0.07 sec
        Start  99: engine_kml_cache
 99/130 Test  #99: engine_kml_cache .........................   Passed    0.06 sec
        Start 100: engine_kml_file
100/130 Test #100: engine_kml_file ..........................   Passed    0.03 sec
        Start 101: engine_kml_stream
101/130 Test #101: engine_kml_stream ........................   Passed    0.87 sec
        Start 102: engine_kml_uri
102/130 Test #102: engine_kml_uri ...........................   Passed    0.02 sec
        Start 103: engine_kmz_file
103/130 Test #103: engine_kmz_file ..........................   Passed    0.09 sec
        Start 104: engine_link_util
104/130 Test #104: engine_link_util .........................   Passed    0.01 sec
        Start 105: engine_location_util
105/130 Test #105: engine_location_util .....................   Passed    0.08 sec
        Start 106: engine_merge
106/130 Test #106: engine_merge .............................   Passed    0.01 sec
        Start 107: engine_object_id_parser_observer
107/130 Test #107: engine_object_id_parser_observer .........   Passed    0.02 sec
        Start 108: engine_old_schema_parser_observer
108/130 Test #108: engine_old_schema_parser_observer ........   Passed    0.01 sec
        Start 109: engine_parse_old_schema
109/130 Test #109: engine_parse_old_schema ..................   Passed    0.01 sec
        Start 110: engine_schema_parser_observer
110/130 Test #110: engine_schema_parser_observer ............   Passed    0.02 sec
        Start 111: engine_shared_style_parser_observer
111/130 Test #111: engine_shared_style_parser_observer ......   Passed    0.02 sec
        Start 112: engine_style_inliner
112/130 Test #112: engine_style_inliner .....................   Passed    0.09 sec
        Start 113: engine_style_merger
113/130 Test #113: engine_style_merger ......................   Passed    0.03 sec
        Start 114: engine_style_resolver
114/130 Test #114: engine_style_resolver ....................   Passed    0.18 sec
        Start 115: engine_style_splitter
115/130 Test #115: engine_style_splitter ....................   Passed    0.02 sec
        Start 116: engine_update_processor
116/130 Test #116: engine_update_processor ..................   Passed    0.01 sec
        Start 117: engine_update
117/130 Test #117: engine_update ............................   Passed    0.13 sec
        Start 118: regionator_feature_list_region_handler
118/130 Test #118: regionator_feature_list_region_handler ...   Passed    0.03 sec
        Start 119: regionator_regionator
119/130 Test #119: regionator_regionator ....................   Passed    0.03 sec
        Start 120: regionator_regionator_qid
120/130 Test #120: regionator_regionator_qid ................   Passed    0.01 sec
        Start 121: regionator_regionator_util
121/130 Test #121: regionator_regionator_util ...............   Passed    0.02 sec
        Start 122: xsd_xsd_complex_type
122/130 Test #122: xsd_xsd_complex_type .....................   Passed    0.01 sec
        Start 123: xsd_xsd_file
123/130 Test #123: xsd_xsd_file .............................   Passed    0.03 sec
        Start 124: xsd_xsd_element
124/130 Test #124: xsd_xsd_element ..........................   Passed    0.01 sec
        Start 125: xsd_xsd_handler
125/130 Test #125: xsd_xsd_handler ..........................   Passed    0.04 sec
        Start 126: xsd_xsd_primitive_type
126/130 Test #126: xsd_xsd_primitive_type ...................   Passed    0.02 sec
        Start 127: xsd_xsd_simple_type
127/130 Test #127: xsd_xsd_simple_type ......................   Passed    0.02 sec
        Start 128: xsd_xsd_schema
128/130 Test #128: xsd_xsd_schema ...........................   Passed    0.02 sec
        Start 129: xsd_xsd_util
129/130 Test #129: xsd_xsd_util .............................   Passed    0.01 sec
        Start 130: xsd_xst_parser
130/130 Test #130: xsd_xst_parser ...........................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 130

Total Test time (real) =   5.04 sec
```

Some amount of Python SWIG functionality is tested in src/swig/kmldom\_test.py
and src/swig/kmlengine\_test.py. A successful run of these tests looks as follows:

```
.......................................
----------------------------------------------------------------------
Ran 39 tests in 0.013s

OK
```

And so on. If any tests fail to pass, you will be asked to report the issue to
this project's issue tracker.
