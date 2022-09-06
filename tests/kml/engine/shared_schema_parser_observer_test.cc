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

// This file contains the unit tests for the SharedSchemaParserObserver class.

#include "kml/engine/shared_schema_parser_observer.h"
#include "boost/scoped_ptr.hpp"
#include "kml/dom/kml_factory.h"
#include "gtest/gtest.h"

namespace kmlengine {

class SharedSchemaParserObserverTest : public testing::Test {
 protected:
  virtual void SetUp() {
    // Make some elements used in most tests.
    kmldom::KmlFactory* factory = kmldom::KmlFactory::GetFactory();
    document_ = factory->CreateDocument();
    folder_ = factory->CreateFolder();
    kSchema0Id_ = "schema0";
    schema0_ = factory->CreateSchema();
    schema0_->set_id(kSchema0Id_);
    kSchema1Id_ = "schema1";
    schema1_ = factory->CreateSchema();
    schema1_->set_id(kSchema1Id_);
    schema_no_id_ = factory->CreateSchema();
    // Create a non-strict SharedSchemaParserObserver.
    shared_schema_parser_observer_.reset(
        new SharedSchemaParserObserver(&shared_schema_map_, false));
  }

  kmldom::DocumentPtr document_;
  kmldom::FolderPtr folder_;
  std::string kSchema0Id_;
  kmldom::SchemaPtr schema0_;
  std::string kSchema1Id_;
  kmldom::SchemaPtr schema1_;
  kmldom::SchemaPtr schema_no_id_;
  SharedSchemaMap shared_schema_map_;
  boost::scoped_ptr<SharedSchemaParserObserver> shared_schema_parser_observer_;
};

// Verify that AddChild() accepts shared Schemas.
TEST_F(SharedSchemaParserObserverTest, TestAddChildSharedSchema) {
  // Verify that AddChild() does not detect a dupe.
  ASSERT_TRUE(shared_schema_parser_observer_->AddChild(document_, schema0_));
  // Verify that there is only one entry in the map.
  ASSERT_EQ(static_cast<size_t>(1), shared_schema_map_.size());

  // Verify that the id maps to the Style.
  kmldom::SchemaPtr object = shared_schema_map_[kSchema0Id_];
  ASSERT_EQ(kSchema0Id_, object->get_id());
  ASSERT_EQ(kmldom::Type_Schema, object->Type());

  // Verify that AddChild() does not detect a dupe.
  ASSERT_TRUE(shared_schema_parser_observer_->AddChild(document_, schema1_));
  // Verify that there are now 2 entries in the map.
  ASSERT_EQ(static_cast<size_t>(2), shared_schema_map_.size());
  // Verify that the id maps to Schema #1
  object = shared_schema_map_[kSchema1Id_];
  ASSERT_EQ(kSchema1Id_, object->get_id());
  ASSERT_EQ(kmldom::Type_Schema, object->Type());
}

// Verify that NewElement() exists and alwyas returns true.
TEST_F(SharedSchemaParserObserverTest, TestNewElement) {
  // Verify that NewElement() accepts StyleSelectors.
  ASSERT_TRUE(shared_schema_parser_observer_->NewElement(schema0_));
  // Verify that a 2nd call succeeds given that NewElement is a nop
  ASSERT_TRUE(shared_schema_parser_observer_->NewElement(schema0_));
  ASSERT_TRUE(shared_schema_parser_observer_->NewElement(schema1_));
  // Style with no id accepted fine:
  ASSERT_TRUE(shared_schema_parser_observer_->NewElement(schema_no_id_));
  // Document, Folder both fine...
  ASSERT_TRUE(shared_schema_parser_observer_->NewElement(folder_));
  ASSERT_TRUE(shared_schema_parser_observer_->NewElement(document_));
}

// Verify that AddChild() properly detects a duplicate Object id when
// strict_parse is true.
TEST_F(SharedSchemaParserObserverTest, TestAddChildDetectsDupeId) {
  boost::scoped_ptr<SharedSchemaParserObserver> shared_style_parser_observer(
      new SharedSchemaParserObserver(&shared_schema_map_, true));
  // Pass a parent-child that will be added to the map.
  ASSERT_TRUE(shared_style_parser_observer->AddChild(document_, schema0_));
  // Verify that AddChild() detected the dupe.
  ASSERT_FALSE(shared_style_parser_observer->AddChild(document_, schema0_));
  // Verify that the map was not affected.
  ASSERT_EQ(static_cast<size_t>(1), shared_schema_map_.size());
  kmldom::ObjectPtr object = shared_schema_map_[kSchema0Id_];
  ASSERT_EQ(kSchema0Id_, object->get_id());
  ASSERT_EQ(kmldom::Type_Schema, object->Type());
}

// Verify that the destructor does not affect the map.
TEST_F(SharedSchemaParserObserverTest, TestDestructor) {
  // Use AddChild() to put some entries in the map.
  ASSERT_TRUE(shared_schema_parser_observer_->AddChild(document_, schema0_));
  ASSERT_TRUE(shared_schema_parser_observer_->AddChild(document_, schema1_));

  // Verify that deleting the observer does not affect the map.
  shared_schema_parser_observer_.reset();

  // Verify that the object map has exactly the 2 expected mappings.
  ASSERT_EQ(static_cast<size_t>(2), shared_schema_map_.size());
  ASSERT_EQ(kSchema0Id_, shared_schema_map_[kSchema0Id_]->get_id());
  ASSERT_EQ(kSchema1Id_, shared_schema_map_[kSchema1Id_]->get_id());
}

}  // end namespace kmlengine
