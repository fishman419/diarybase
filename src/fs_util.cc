#include "fs_util.h"
#include "log.h"
#include "types.h"

#include <fcntl.h>
#include <unistd.h>

namespace diarybase_internal {

DiaryFile *DiaryFile::Open(const std::string &path, bool create) {
  // TODO(yyt): mkdir -p path
  int fd;
  std::string file = path + "/" + kDiaryFileName;
  int flags = O_RDWR | O_APPEND | O_CLOEXEC;
  if (create) {
    flags |= O_CREAT;
    flags |= O_EXCL;
    fd = open(file.c_str(), flags, 0755);
  } else {
    fd = open(file.c_str(), flags);
  }
  if (fd < 0) {
    LOG(ERR) << "open file error, errno: " << errno << ", path: " << path
             << "\n";
    return nullptr;
  }
  auto f = new DiaryFile(fd);
  return f;
}

void DiaryFile::Close(DiaryFile *file) { delete file; }

DiaryFile::DiaryFile(int fd) : fd_(fd) {}

DiaryFile::~DiaryFile() {
  if (fd_ > 0) {
    close(fd_);
  }
}

int DiaryFile::Read(char *buffer, uint64_t length) {
  return read(fd_, buffer, length);
}

int DiaryFile::Append(char *buffer, uint64_t length) {
  return write(fd_, buffer, length);
}

int DiaryFile::PRead(uint64_t offset, uint64_t length, char *buffer) {
  return pread(fd_, buffer, length, offset);
}

int DiaryFile::PWrite(uint64_t offset, uint64_t length, char *buffer) {
  return pwrite(fd_, buffer, length, offset);
}

int64_t DiaryFile::GetPos() { return lseek(fd_, 0, SEEK_CUR); }

} // namespace diarybase_internal
