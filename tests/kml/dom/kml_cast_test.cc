// Copyright 2008, Google Inc. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
//
//  1. Redistributions of source code must retain the above copyright notice, 
//     this list of conditions and the following disclaimer.
//  2. Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//  3. Neither the name of Google Inc. nor the names of its contributors may be
//     used to endorse or promote products derived from this software without
//     specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
// EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "kml/dom/kml_cast.h"
#include "kml/dom/kml_factory.h"
#include "kml/dom/kmldom.h"
#include "gtest/gtest.h"

namespace kmldom {

class KmlCastTest : public testing::Test {
};

TEST_F(KmlCastTest, TestCasts) {
  KmlFactory* factory = KmlFactory::GetFactory();

  // The temporary ElementPtr holds a reference to the created Element
  // which is released when the As*() goes out of scope.
  ASSERT_TRUE(AsAbstractLatLonBox(factory->CreateElementById(Type_LatLonBox)) != 0);
  ASSERT_TRUE(AsAbstractLatLonBox(
      factory->CreateElementById(Type_LatLonAltBox)) != 0);
  ASSERT_TRUE(AsAbstractView(factory->CreateElementById(Type_LookAt)) != 0);
  ASSERT_TRUE(AsColorStyle(factory->CreateElementById(Type_IconStyle)) != 0);
  ASSERT_TRUE(AsContainer(factory->CreateElementById(Type_Folder)) != 0);
  ASSERT_TRUE(AsFeature(factory->CreateElementById(Type_Placemark)) != 0);
  ASSERT_TRUE(AsGeometry(factory->CreateElementById(Type_Point)) != 0);
  ASSERT_TRUE(AsObject(factory->CreateElementById(Type_Placemark)) != 0);
  ASSERT_TRUE(AsOverlay(factory->CreateElementById(Type_GroundOverlay)) != 0);
  ASSERT_TRUE(AsStyleSelector(factory->CreateElementById(Type_Style)) != 0);
  ASSERT_TRUE(AsSubStyle(factory->CreateElementById(Type_BalloonStyle)) != 0);
  ASSERT_TRUE(AsTimePrimitive(factory->CreateElementById(Type_TimeSpan)) != 0);
  ASSERT_TRUE(AsAlias(factory->CreateElementById(Type_Alias)) != 0);
  ASSERT_TRUE(AsAtomAuthor(factory->CreateElementById(Type_AtomAuthor)) != 0);
  ASSERT_TRUE(AsAtomContent(factory->CreateElementById(Type_AtomContent)) != 0);
  ASSERT_TRUE(AsAtomEntry(factory->CreateElementById(Type_AtomEntry)) != 0);
  ASSERT_TRUE(AsAtomFeed(factory->CreateElementById(Type_AtomFeed)) != 0);
  ASSERT_TRUE(AsAtomLink(factory->CreateElementById(Type_AtomLink)) != 0);
  ASSERT_TRUE(AsBalloonStyle(factory->CreateElementById(Type_BalloonStyle)) != 0);
  ASSERT_TRUE(AsCamera(factory->CreateElementById(Type_Camera)) != 0);
  ASSERT_TRUE(AsChange(factory->CreateElementById(Type_Change)) != 0);
  ASSERT_TRUE(AsCoordinates(factory->CreateElementById(Type_coordinates)) != 0);
  ASSERT_TRUE(AsCreate(factory->CreateElementById(Type_Create)) != 0);
  ASSERT_TRUE(AsData(factory->CreateElementById(Type_Data)) != 0);
  ASSERT_TRUE(AsDelete(factory->CreateElementById(Type_Delete)) != 0);
  ASSERT_TRUE(AsDocument(factory->CreateElementById(Type_Document)) != 0);
  ASSERT_TRUE(AsExtendedData(factory->CreateElementById(Type_ExtendedData)) != 0);
  ASSERT_TRUE(AsFolder(factory->CreateElementById(Type_Folder)) != 0);
  ASSERT_TRUE(AsGroundOverlay(
      factory->CreateElementById(Type_GroundOverlay)) != 0);
  ASSERT_TRUE(AsHotSpot(factory->CreateElementById(Type_hotSpot)) != 0);
  ASSERT_TRUE(AsIcon(factory->CreateElementById(Type_Icon)) != 0);
  ASSERT_TRUE(AsIconStyle(factory->CreateElementById(Type_IconStyle)) != 0);
  ASSERT_TRUE(AsImagePyramid(factory->CreateElementById(Type_ImagePyramid)) != 0);
  ASSERT_TRUE(AsInnerBoundaryIs(
      factory->CreateElementById(Type_innerBoundaryIs)) != 0);
  ASSERT_TRUE(AsItemIcon(factory->CreateElementById(Type_ItemIcon)) != 0);
  ASSERT_TRUE(AsLabelStyle(factory->CreateElementById(Type_LabelStyle)) != 0);
  ASSERT_TRUE(AsLatLonAltBox(factory->CreateElementById(Type_LatLonAltBox)) != 0);
  ASSERT_TRUE(AsLatLonBox(factory->CreateElementById(Type_LatLonBox)) != 0);
  ASSERT_TRUE(AsLineString(factory->CreateElementById(Type_LineString)) != 0);
  ASSERT_TRUE(AsLineStyle(factory->CreateElementById(Type_LineStyle)) != 0);
  ASSERT_TRUE(AsLinearRing(factory->CreateElementById(Type_LinearRing)) != 0);
  ASSERT_TRUE(AsLink(factory->CreateElementById(Type_Link)) != 0);
  ASSERT_TRUE(AsLinkSnippet(factory->CreateElementById(Type_linkSnippet)) != 0);
  ASSERT_TRUE(AsListStyle(factory->CreateElementById(Type_ListStyle)) != 0);
  ASSERT_TRUE(AsLocation(factory->CreateElementById(Type_Location)) != 0);
  ASSERT_TRUE(AsLod(factory->CreateElementById(Type_Lod)) != 0);
  ASSERT_TRUE(AsLookAt(factory->CreateElementById(Type_LookAt)) != 0);
  ASSERT_TRUE(AsKml(factory->CreateElementById(Type_kml)) != 0);
  ASSERT_TRUE(AsModel(factory->CreateElementById(Type_Model)) != 0);
  ASSERT_TRUE(AsMultiGeometry(
      factory->CreateElementById(Type_MultiGeometry)) != 0);
  ASSERT_TRUE(AsNetworkLink(factory->CreateElementById(Type_NetworkLink)) != 0);
  ASSERT_TRUE(AsNetworkLinkControl(
      factory->CreateElementById(Type_NetworkLinkControl)) != 0);
  ASSERT_TRUE(AsOrientation(factory->CreateElementById(Type_Orientation)) != 0);
  ASSERT_TRUE(AsOuterBoundaryIs(
      factory->CreateElementById(Type_outerBoundaryIs)) != 0);
  ASSERT_TRUE(AsOverlayXY(factory->CreateElementById(Type_overlayXY)) != 0);
  ASSERT_TRUE(AsPair(factory->CreateElementById(Type_Pair)) != 0);
  ASSERT_TRUE(AsPhotoOverlay(factory->CreateElementById(Type_PhotoOverlay)) != 0);
  ASSERT_TRUE(AsPlacemark(factory->CreateElementById(Type_Placemark)) != 0);
  ASSERT_TRUE(AsPoint(factory->CreateElementById(Type_Point)) != 0);
  ASSERT_TRUE(AsPolyStyle(factory->CreateElementById(Type_PolyStyle)) != 0);
  ASSERT_TRUE(AsPolygon(factory->CreateElementById(Type_Polygon)) != 0);
  ASSERT_TRUE(AsRegion(factory->CreateElementById(Type_Region)) != 0);
  ASSERT_TRUE(AsResourceMap(factory->CreateElementById(Type_ResourceMap)) != 0);
  ASSERT_TRUE(AsRotationXY(factory->CreateElementById(Type_rotationXY)) != 0);
  ASSERT_TRUE(AsScale(factory->CreateElementById(Type_Scale)) != 0);
  ASSERT_TRUE(AsSchema(factory->CreateElementById(Type_Schema)) != 0);
  ASSERT_TRUE(AsSchemaData(factory->CreateElementById(Type_SchemaData)) != 0);
  ASSERT_TRUE(AsScreenOverlay(
      factory->CreateElementById(Type_ScreenOverlay)) != 0);
  ASSERT_TRUE(AsScreenXY(factory->CreateElementById(Type_screenXY)) != 0);
  ASSERT_TRUE(AsSimpleData(factory->CreateElementById(Type_SimpleData)) != 0);
  ASSERT_TRUE(AsSimpleField(factory->CreateElementById(Type_SimpleField)) != 0);
  ASSERT_TRUE(AsSize(factory->CreateElementById(Type_size)) != 0);
  ASSERT_TRUE(AsSnippet(factory->CreateElementById(Type_Snippet)) != 0);
  ASSERT_TRUE(AsStyle(factory->CreateElementById(Type_Style)) != 0);
  ASSERT_TRUE(AsStyleMap(factory->CreateElementById(Type_StyleMap)) != 0);
  ASSERT_TRUE(AsTimeSpan(factory->CreateElementById(Type_TimeSpan)) != 0);
  ASSERT_TRUE(AsTimeStamp(factory->CreateElementById(Type_TimeStamp)) != 0);
  ASSERT_TRUE(AsUpdate(factory->CreateElementById(Type_Update)) != 0);
  ASSERT_TRUE(AsViewVolume(factory->CreateElementById(Type_ViewVolume)) != 0);

  ASSERT_TRUE(AsXalAddressDetails(
      factory->CreateElementById(Type_XalAddressDetails)) != 0);
  ASSERT_TRUE(AsXalAdministrativeArea(
      factory->CreateElementById(Type_XalAdministrativeArea)) != 0);
  ASSERT_TRUE(AsXalCountry(factory->CreateElementById(Type_XalCountry)) != 0);
  ASSERT_TRUE(AsXalLocality(factory->CreateElementById(Type_XalLocality)) != 0);
  ASSERT_TRUE(AsXalPostalCode(factory->CreateElementById(Type_XalPostalCode)) != 0);
  ASSERT_TRUE(AsXalSubAdministrativeArea(
      factory->CreateElementById(Type_XalSubAdministrativeArea)) != 0);
  ASSERT_TRUE(AsXalThoroughfare(
      factory->CreateElementById(Type_XalThoroughfare)) != 0);

  ASSERT_TRUE(AsGxAnimatedUpdate(
      factory->CreateElementById(Type_GxAnimatedUpdate)) != 0);
  ASSERT_TRUE(AsGxFlyTo(
      factory->CreateElementById(Type_GxFlyTo)) != 0);
  ASSERT_TRUE(AsGxLatLonQuad(
      factory->CreateElementById(Type_GxLatLonQuad)) != 0);
  ASSERT_TRUE(AsGxMultiTrack(
      factory->CreateElementById(Type_GxMultiTrack)) != 0);
  ASSERT_TRUE(AsGxPlaylist(
      factory->CreateElementById(Type_GxPlaylist)) != 0);
  ASSERT_TRUE(AsGxSimpleArrayField(
      factory->CreateElementById(Type_GxSimpleArrayField)) != 0);
  ASSERT_TRUE(AsGxSimpleArrayData(
      factory->CreateElementById(Type_GxSimpleArrayData)) != 0);
  ASSERT_TRUE(AsGxSoundCue(
      factory->CreateElementById(Type_GxSoundCue)) != 0);
  ASSERT_TRUE(AsGxTimeSpan(
      factory->CreateElementById(Type_GxTimeSpan)) != 0);
  ASSERT_TRUE(AsTimeSpan(
      factory->CreateElementById(Type_GxTimeSpan)) != 0);
  ASSERT_TRUE(AsGxTimeStamp(
      factory->CreateElementById(Type_GxTimeStamp)) != 0);
  ASSERT_TRUE(AsTimeStamp(
      factory->CreateElementById(Type_GxTimeStamp)) != 0);
  ASSERT_TRUE(AsTimePrimitive(
      factory->CreateElementById(Type_GxTimeSpan)) != 0);
  ASSERT_TRUE(AsTimePrimitive(
      factory->CreateElementById(Type_GxTimeStamp)) != 0);
  ASSERT_TRUE(AsGxTour(
      factory->CreateElementById(Type_GxTour)) != 0);
  ASSERT_TRUE(AsGxTourControl(
      factory->CreateElementById(Type_GxTourControl)) != 0);
  ASSERT_TRUE(AsGxTourPrimitive(
      factory->CreateElementById(Type_GxFlyTo)) != 0);
  ASSERT_TRUE(AsGxTrack(
      factory->CreateElementById(Type_GxTrack)) != 0);
  ASSERT_TRUE(AsGxWait(
      factory->CreateElementById(Type_GxWait)) != 0);
}

}  // end namespace kmldom
