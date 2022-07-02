#include "fs_util.h"

#include <fcntl.h>
#include <unistd.h>

namespace diarybase_internal {

DiaryFile *DiaryFile::Open(const std::string &path, bool create) {}

void DiaryFile::Close(DiaryFile *file) {}

DiaryFile::DiaryFile() {}

DiaryFile::~DiaryFile() {}

int DiaryFile::Read(char *buffer, uint64_t length) { return 0; }

int DiaryFile::Append(char *buffer, uint64_t length) { return 0; }

int DiaryFile::PRead(uint64_t offset, uint64_t length, char *buffer) {
  return 0;
}

} // namespace diarybase_internal
