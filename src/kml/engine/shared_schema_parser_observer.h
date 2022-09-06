// Copyright 2022, Google LLC. All rights reserved.
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

// This file contains the definition of the SharedSchemaParserObserver class.

#ifndef KML_ENGINE_SHARED_SCHEMA_PARSER_OBSERVER_H__
#define KML_ENGINE_SHARED_SCHEMA_PARSER_OBSERVER_H__

#include <map>
#include <string>

#include "kml/dom.h"
#include "kml/dom/parser_observer.h"
#include "kml/engine/engine_types.h"

namespace kmlengine {

// The SharedSchemaParserObserver is a kmldom::ParserObserver which gathers all
// all shared Schemas into the supplied SharedSchemaMap.  If strict_parse
// is true AddChild() returns false on any id collision causing the parse to
// terminate when this is used with kmldom::Parse::AddObserver().  If
// strict_parse is false the "last one wins" on any duplicate.
class SharedSchemaParserObserver : public kmldom::ParserObserver {
 public:
  // A SharedSchemaMap must be supplied.
  SharedSchemaParserObserver(SharedSchemaMap* const shared_schema_map,
                             const bool strict_parse)
      : shared_schema_map_(shared_schema_map), strict_parse_(strict_parse) {}

  virtual ~SharedSchemaParserObserver() {}

  // ParserObserver::AddChild()
  virtual bool AddChild(const kmldom::ElementPtr& parent,
                        const kmldom::ElementPtr& child) {
    // A shared Schema is one with an id that is a child of a Document. If this
    // id already has a mapping return false to terminate the parse.
    if (kmldom::DocumentPtr document = kmldom::AsDocument(parent)) {
      if (kmldom::SchemaPtr sp = kmldom::AsSchema(child)) {
        if (sp->has_id()) {
          if (strict_parse_ && shared_schema_map_->find(sp->get_id()) !=
                                   shared_schema_map_->end()) {
            return false;  // Duplicate id, fail parse.
          }
        }
        // No such mapping so save it, and "last one wins" on non-strict parse.
        (*shared_schema_map_)[sp->get_id()] = sp;
      }
    }
    return true;  // Not a duplicate id, keep parsing.
  }

 private:
  SharedSchemaMap* shared_schema_map_;
  bool strict_parse_;
};

}  // end namespace kmlengine

#endif  // KML_ENGINE_SHARED_SCHEMA_PARSER_OBSERVER_H__
