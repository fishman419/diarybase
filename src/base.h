#ifndef DIARYBASE_BASE_
#define DIARYBASE_BASE_

#include <string>

#include "fs_util.h"
#include "index.h"
#include "types.h"

namespace diarybase_internal {

class Base {
public:
  static Base *Create(const std::string &path, const std::string &title,
                      const std::string &author);
  static Base *Open(const std::string &path);
  static int Close(Base *base);
  uint64_t GetDiaryCount();
  int Get(uint64_t id, char *buffer);
  int Put(char *buffer, uint64_t size);

private:
  int Init(const std::string &title, const std::string &author);
  int Load();
  Base(DiaryFile *file, const std::string &path);
  ~Base();

  std::string path_;
  DiaryFile *file_;
  uint64_t pos_;
  DiaryMeta meta_;
  IndexTable table_;
};

} // namespace diarybase_internal
#endif