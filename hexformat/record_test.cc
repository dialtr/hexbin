// Copyright (C) 2026 The hexbin authors. All rights reserved.
#include "hexformat/record.h"

#include <gtest/gtest.h>

#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

#include "absl/status/status.h"
#include "absl/status/statusor.h"

using std::cerr;
using std::cout;
using std::endl;

TEST(Record, ReadWithChecksumValidation) {
  const std::string data(":03123400010203B1");
  std::stringstream ss(data);
  const Record::ReadOptions read_opts{.validate_checksum{true}};
  absl::StatusOr<Record> result = Record::Read(ss, read_opts);
  EXPECT_TRUE(result.ok());

  Record rec(std::move(result.value()));

  EXPECT_EQ(3, rec.byte_count());
  EXPECT_EQ(0x1234, rec.address());
  EXPECT_EQ(0, rec.record_type());
  EXPECT_EQ(0x1, rec.data()[0]);
  EXPECT_EQ(0x2, rec.data()[1]);
  EXPECT_EQ(0x3, rec.data()[2]);
  EXPECT_EQ(0xb1, rec.provided_checksum());
  EXPECT_EQ(0xb1, rec.calculated_checksum());
  EXPECT_TRUE(rec.IsChecksumValid());
}

TEST(Record, ReadNoChecksumValidation) {
  const std::string data(":0312340001020300");
  std::stringstream ss(data);
  const Record::ReadOptions read_opts{.validate_checksum{false}};
  absl::StatusOr<Record> result = Record::Read(ss, read_opts);
  EXPECT_TRUE(result.ok());

  Record rec(std::move(result.value()));

  EXPECT_EQ(3, rec.byte_count());
  EXPECT_EQ(0x1234, rec.address());
  EXPECT_EQ(0, rec.record_type());
  EXPECT_EQ(0x1, rec.data()[0]);
  EXPECT_EQ(0x2, rec.data()[1]);
  EXPECT_EQ(0x3, rec.data()[2]);
  EXPECT_EQ(0x00, rec.provided_checksum());
  EXPECT_EQ(0xb1, rec.calculated_checksum());
  EXPECT_FALSE(rec.IsChecksumValid());
}

TEST(Record, ReadBadWithChecksumValidation) {
  const std::string data(":0312340001020300");
  std::stringstream ss(data);
  const Record::ReadOptions read_opts{.validate_checksum{true}};
  absl::StatusOr<Record> result = Record::Read(ss, read_opts);
  EXPECT_FALSE(result.ok());
}

TEST(Record, ReadEofRecord) {
  const std::string data(":00000001FF");
  std::stringstream ss(data);
  const Record::ReadOptions read_opts{.validate_checksum{true}};
  absl::StatusOr<Record> result = Record::Read(ss, read_opts);
  EXPECT_TRUE(result.ok());
  EXPECT_TRUE(result.value().IsEof());
}
