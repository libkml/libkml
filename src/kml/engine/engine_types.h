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

// This file containts typedefs and declarations common within KML Engine.

#ifndef KML_ENGINE_ENGINE_TYPES_H__
#define KML_ENGINE_ENGINE_TYPES_H__

#include <map>
#include <vector>
#include "kml/dom.h"

namespace kmlengine {

// This is a vector Elements used in a variety of places in the KML engine.
typedef std::vector<kmldom::ElementPtr> ElementVector;

// The SharedStyleParserObserver class uses this data structure to map the XML
// id to a kmldom::StyleSelectorPtr.
typedef std::map<string, kmldom::StyleSelectorPtr> SharedStyleMap;

// The SharedSchemaParserObserver class uses this data structure to map the XML
// id to a kmldom::SchemaPtr.
typedef std::map<std::string, kmldom::SchemaPtr> SharedSchemaMap;

// The ObjectIdParserObserver class uses this data structure to map the XML
// id to a kmldom::ObjectPtr.
typedef std::map<string, kmldom::ObjectPtr> ObjectIdMap;

// The SchemaParserObserver class uses this data structure to map the <Schema>
// name= to a kmldom::SchemaPtr.
typedef std::map<string, kmldom::SchemaPtr> SchemaNameMap;

}  // end namespace kmlengine

#endif  // KML_ENGINE_ENGINE_TYPES_H__
