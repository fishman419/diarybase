#ifndef DIARYBASE_STRUCTURE_
#define DIARYBASE_STRUCTURE_

#include <stdint.h>
// "DiaryBas"
static const uint64_t kDiaryMagic1 = 0x44696172;
static const uint64_t kDiaryMagic2 = 0x79426173;
static const uint64_t kTitleLength = 256;
static const uint64_t kAuthorLength = 128;

struct DiaryMeta {
  uint64_t diary_magic1;
  uint64_t diary_magic2;
  uint64_t version;
  char title[kTitleLength];
  char author[kAuthorLength];
  uint64_t create_timestamp;
  uint64_t update_timestamp;
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