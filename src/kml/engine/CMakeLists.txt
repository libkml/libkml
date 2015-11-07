file(GLOB SRCS "*.cc" )

set(INCS
  bbox.h
  clone.h
  engine_types.h
  entity_mapper.h
  feature_balloon.h
  feature_view.h
  feature_visitor.h
  find.h
  find_xml_namespaces.h
  get_link_parents.h
  get_links.h
  href.h
  id_mapper.h
  kml_cache.h
  kml_file.h
  kml_stream.h
  kml_uri.h
  kmz_cache.h
  kmz_file.h
  link_util.h
  location_util.h
  merge.h
  object_id_parser_observer.h
  old_schema_parser_observer.h
  parse_old_schema.h
  schema_parser_observer.h
  shared_style_parser_observer.h
  style_inliner.h
  style_merger.h
  style_resolver.h
  style_splitter.h
  update.h)

build_target(
  NAME kmlengine
  SRCS ${SRCS}
  INCS ${INCS}
  DEPENDS kmlbase;kmldom)


