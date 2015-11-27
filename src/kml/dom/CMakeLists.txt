file(GLOB SRCS "*.cc" )
set(INCS
  abstractlatlonbox.h
  abstractview.h
  atom.h
  balloonstyle.h
  colorstyle.h
  container.h
  document.h
  element.h
  extendeddata.h
  feature.h
  folder.h
  geometry.h
  hotspot.h
  iconstyle.h
  kml.h
  kml22.h
  kml_cast.h
  kml_factory.h
  kml_funcs.h
  kml_ptr.h
  kmldom.h
  labelstyle.h
  linestyle.h
  link.h
  liststyle.h
  model.h
  networklink.h
  networklinkcontrol.h
  object.h
  overlay.h
  parser.h
  parser_observer.h
  placemark.h
  polystyle.h
  region.h
  schema.h
  snippet.h
  style.h
  stylemap.h
  styleselector.h
  substyle.h
  timeprimitive.h
  gx_timeprimitive.h
  gx_tour.h
  vec2.h
  xal.h
  xsd.h
  visitor.h
  visitor_driver.h)

build_target(
  NAME kmldom
  SRCS ${SRCS}
  INCS ${INCS}  
  DEPENDS kmlbase)

