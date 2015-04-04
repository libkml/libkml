#summary libkml reference
#labels Featured

This is a reference to programming with libkml.

# Overview #

  * QuickStart
  * [KML Base](KmlBaseReference.md)
  * [KML Dom](KmlDomReference.md)
  * [KML Engine](KmlEngineReference.md)
  * [KML Convenience](KmlConvenienceReference.md)
  * [KML Regionator](KmlRegionatorReference.md)
  * KML XSD

The KML base library is internal to the libkml system.  There is no public API
to this module, but this must be linked with any use of libkml.

The KML DOM is the API to KML data which is a direct representation of the XML.
Everything you can
do in XML you can do in the DOM API.  KML DOM requires KML Base.

The KML Engine is the API to KML algorithms such as semantics and behavior
specified by the KML standard beyond the basic XML file format.
KML Engine requires KML DOM and KML Base.

The KML Convenience library consists of useful and common
utility code not directly part of the KML standard.  KML Convenience
requires KML Engine, KML DOM and KML Base.

The KML Regionator library consists of code useful for creating
Region-based NetworkLink hierarchies.  KML Regionator depends
on KML Convenience, KML Engine, KML DOM, and KML Base.

The KML XSD library includes code to proces the KML XSD.