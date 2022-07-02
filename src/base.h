#ifndef DIARYBASE_BASE_
#define DIARYBASE_BASE_

#include <string>

#include "fs_util.h"
#include "index.h"

namespace diarybase_internal {

class Base {
public:
  static Base *Open(const std::string &path);
  static int Close(Base *base);
  uint64_t GetDiaryCount();

private:
  Base(DiaryFile *file, const std::string &path);
  ~Base();

  std::string path_;
  DiaryFile *file_;
  IndexTable table_;
};

} // namespace diarybase_internal
#endif