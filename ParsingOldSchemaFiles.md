#summary Parsing old 

&lt;Schema&gt;

 usage

Prior to standardization, KML 2.0 and 2.1 permitted the extension of the Placemark element like so:

```
<Document>
  <Schema parent="Placemark" name="MyExtendedPlacemark">
    <SimpleField type="string" name="someNewChild"></SimpleField>
  </Schema>
  <MyExtendedPlacemark>
    <someNewChild>your string here</someNewChild>
  </MyExtendedPlacemark>
</Document>
```

Google Earth Pro 5.1 and earlier emitted this style of markup when a shapefile (.SHP) was ingested. The intent was to permit the lossless conversion of other geospatial file formats to KML, but ultimately this practice was superseded in KML 2.2 by the use of [ExtendedData](http://code.google.com/apis/kml/documentation/extendeddata.html) which allows the addition of typed data to any Feature.

However, developers who have to deal with real-world KML know that the [web is littered](http://www.google.com/search?q=filetype:kml+"schema+parent%3Dplacemark") with old KML files that use `<Schema>` in this way, as well as countless files in private storage. They'll be there for a long time, so, in the spirit of [Postel](http://en.wikipedia.org/wiki/Jon_Postel#Postel.27s_Law), libkml attempts to parse this style of markup. In the case of the above example, it will be parsed like so:

```
<Document>
  <Schema id="MyExtendedPlacemark_id" name="MyExtendedPlacemark">
    <SimpleField name="Foo" type="string"/>
  </Schema>
  <Placemark>
    <ExtendedData>
      <SchemaData schemaUrl="MyExtendedPlacemark_id">
        <SimpleData name="someNewChild">your string here</SimpleData>
      </SchemaData>
    </ExtendedData>
  </Placemark>
</Document>
```

If loaded into any recent version of Google Earth, both of those files produce equivalent displays and interaction models.

Change [r798](http://code.google.com/p/libkml/source/detail?r=798) introduced this new behavior.