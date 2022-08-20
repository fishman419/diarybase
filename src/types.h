#ifndef DIARYBASE_TYPES_
#define DIARYBASE_TYPES_

#include <stdint.h>
// "DiaryBas"
static const uint64_t kDiaryMagic = 0x7361427972616944;
static const uint64_t kCurrentVersion = 1;
static const uint64_t kTitleLength = 256;
static const uint64_t kAuthorLength = 128;
static const uint64_t kMaxBufferSize = 8192;
static const char kDiaryFileName[] = "diary.db";

/* Storage Layout
 * [Meta][Data1][Data2][Data3]...
 */

struct DiaryMeta {
  uint64_t diary_magic;
  uint64_t version;
  char title[kTitleLength];
  char author[kAuthorLength];
  uint64_t create_timestamp;
  uint64_t update_timestamp;
  uint64_t next_id;
};

enum DiaryOperation {
  DiaryCreate = 0,
  DiaryUpdate = 1,
  DiaryDelete = 2,
};

struct DiaryData {
  uint64_t id;
  uint64_t timestamp;
  uint32_t opcode;
  uint32_t data_size;
};

#endif