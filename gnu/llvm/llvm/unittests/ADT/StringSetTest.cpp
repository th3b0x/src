//===- llvm/unittest/ADT/StringSetTest.cpp - StringSet unit tests ----------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "llvm/ADT/StringSet.h"
#include "gtest/gtest.h"
using namespace llvm;

namespace {

// Test fixture
class StringSetTest : public testing::Test {};

TEST_F(StringSetTest, IterSetKeys) {
  StringSet<> Set;
  Set.insert("A");
  Set.insert("B");
  Set.insert("C");
  Set.insert("D");

  auto Keys = to_vector<4>(Set.keys());
  llvm::sort(Keys);

  SmallVector<StringRef, 4> Expected = {"A", "B", "C", "D"};
  EXPECT_EQ(Expected, Keys);
}

TEST_F(StringSetTest, InsertAndCountStringMapEntry) {
  // Test insert(StringMapEntry) and count(StringMapEntry)
  // which are required for set_difference(StringSet, StringSet).
  StringSet<> Set;
  StringMapEntry<StringRef> *Element = StringMapEntry<StringRef>::Create("A");
  Set.insert(*Element);
  size_t Count = Set.count(*Element);
  size_t Expected = 1;
  EXPECT_EQ(Expected, Count);
  Element->Destroy();
}

} // end anonymous namespace
