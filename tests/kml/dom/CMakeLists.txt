set(TESTS
abstractlatlonbox
abstractview
atom
balloonstyle
colorstyle
container
document
element
extendeddata
feature
folder
geometry
hotspot
iconstyle
kml_cast
kml
kml_factory
kml22
labelstyle
linestyle
link
liststyle
model
networklink
networklinkcontrol
object
overlay
placemark
polystyle
region
round_trip
schema
snippet
style
stylemap
styleselector
substyle
timeprimitive
vec2
unknown
kml_handler
kml_handler_ns
parser
serializer
gx_timeprimitive
gx_tour
xal
xml_serializer
xsd
visitor
visitor_driver)

foreach(t ${TESTS})
  build_target(
    TEST
    GROUP dom
    NAME ${t}_test
    DEPENDS kmldom)
endforeach()

