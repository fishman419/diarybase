#ifndef DIARYBASE_FS_UTIL_
#define DIARYBASE_FS_UTIL_

#include <string>

namespace diarybase_internal {

class DiaryFile {
public:
  static DiaryFile *Open(const std::string &path, bool create = false);
  static void Close(DiaryFile *file);
  int Read(char *buffer, uint64_t length);
  int Append(char *buffer, uint64_t length);
  int PRead(uint64_t offset, uint64_t length, char *buffer);

private:
  DiaryFile();
  ~DiaryFile();
  int fd_;
  uint64_t pos_;
};

} // namespace diarybase_internal

#endif