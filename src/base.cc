#include "base.h"
#include "structure.h"

namespace diarybase_internal {

Base *Base::Open(const std::string &path) {
  auto file = DiaryFile::Open(path, true);
  if (!file) {
    return nullptr;
  }
  auto base = new Base(file, path);
  return base;
}

int Base::Close(Base *base) {
  if (base) {
    delete base;
  }
  return 0;
}

Base::Base(DiaryFile *file, const std::string &path)
    : path_(path), file_(file) {}

Base::~Base() {
  if (file_) {
    DiaryFile::Close(file_);
  }
}

uint64_t Base::GetDiaryCount() {
  return table_.GetSize();
}

} // namespace diarybase_internal