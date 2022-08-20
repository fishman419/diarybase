#include "base.h"

#include "log.h"
#include "types.h"
#include <string.h>
#include <sys/time.h>

namespace diarybase_internal {

Base *Base::Create(const std::string &path, const std::string &title,
                   const std::string &author) {
  auto file = DiaryFile::Open(path, true);
  if (!file) {
    return nullptr;
  }
  auto base = new Base(file, path);
  int ret = base->Init(title, author);
  if (ret) {
    LOG(ERR) << "Init failed, ret: " << ret << "\n";
    delete base;
    return nullptr;
  }
  return base;
}

Base *Base::Open(const std::string &path) {
  auto file = DiaryFile::Open(path);
  if (!file) {
    return nullptr;
  }
  auto base = new Base(file, path);
  int ret = base->Load();
  if (ret) {
    LOG(ERR) << "Load failed, ret: " << ret << "\n";
    delete base;
    return nullptr;
  }
  return base;
}

int Base::Close(Base *base) {
  if (base) {
    delete base;
  }
  return 0;
}

Base::Base(DiaryFile *file, const std::string &path)
    : path_(path), file_(file), pos_(0) {}

Base::~Base() {
  if (file_) {
    DiaryFile::Close(file_);
  }
}

int Base::Init(const std::string &title, const std::string &author) {
  struct timeval tv;
  gettimeofday(&tv, nullptr);
  size_t title_length =
      (kTitleLength - 1) > title.length() ? title.length() : (kTitleLength - 1);
  size_t author_length = (kAuthorLength - 1) > author.length()
                             ? author.length()
                             : (kAuthorLength - 1);
  memset(&meta_, 0, sizeof(meta_));
  meta_.diary_magic = kDiaryMagic;
  meta_.version = kCurrentVersion;
  strncpy(meta_.title, title.c_str(), title_length);
  meta_.title[title_length] = '\0';
  strncpy(meta_.author, author.c_str(), author_length);
  meta_.author[author_length] = '\0';
  meta_.create_timestamp = tv.tv_sec;
  meta_.update_timestamp = tv.tv_sec;
  meta_.next_id = 0;
  int ret = file_->Append(reinterpret_cast<char *>(&meta_), sizeof(meta_));
  if (ret != sizeof(meta_)) {
    LOG(ERR) << "Append meta failed, ret: " << ret << "\n";
    return -1;
  }
  return 0;
}

int Base::Load() {
  int ret = file_->Read(reinterpret_cast<char *>(&meta_), sizeof(meta_));
  if (ret != sizeof(meta_)) {
    LOG(ERR) << "Read meta failed, ret: " << ret << "\n";
    return -1;
  }
  pos_ += sizeof(meta_);
  ret = 0;
  DiaryData data;
  char buffer[kMaxBufferSize];
  while (true) {
    ret = file_->Read(reinterpret_cast<char *>(&data), sizeof(data));
    if (ret == 0) {
      LOG(INFO) << "Reach EOF, pos: " << pos_ << "\n";
      break;
    }
    if (ret != sizeof(data)) {
      LOG(ERR) << "Read data head failed, ret: " << ret << "\n";
      return -1;
    }
    pos_ += sizeof(data);
    ret = file_->Read(buffer, data.data_size);
    if (static_cast<uint32_t>(ret) != data.data_size) {
      LOG(ERR) << "Read data content failed, ret: " << ret << "\n";
      return -1;
    }
    table_.Insert(data.id, pos_);
    pos_ += data.data_size;
  }
  return 0;
}

uint64_t Base::GetDiaryCount() { return table_.GetSize(); }

int Base::Get(uint64_t id, char *buffer) { return 0; }

int Base::Put(char *buffer, uint64_t size) {
  struct timeval tv;
  gettimeofday(&tv, nullptr);
  // append data
  DiaryData data;
  data.id = meta_.next_id++;
  data.timestamp = tv.tv_sec;
  data.opcode = DiaryCreate;
  data.data_size = size;
  file_->Append(reinterpret_cast<char *>(&data), sizeof(data));
  file_->Append(buffer, size);
  pos_ += sizeof(data);
  table_.Insert(data.id, pos_);
  pos_ += size;
  // update meta
  meta_.update_timestamp = tv.tv_sec;
  file_->PWrite(0, sizeof(meta_), reinterpret_cast<char *>(&meta_));
  return 0;
}

} // namespace diarybase_internal
