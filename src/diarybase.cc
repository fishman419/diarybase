#include "diarybase.h"
#include "base.h"

using diarybase_internal::Base;

static const uint64_t kMaxBufferSize = 8192;

struct diary_base {
  std::string path;
  Base *base;
};

struct diary_base *open_diary(char *path) {
  auto base = Base::Open(path);
  if (!base) {
    return nullptr;
  }
  auto db = new diary_base;
  db->path = path;
  db->base = base;
  return db;
}

int close_diary(struct diary_base *db) {
  if (!db->base) {
    return -1;
  }
  Base::Close(db->base);
  delete db;
  return 0;
}

int get_diary_size(struct diary_base *db, uint64_t *size) {
  if (!db->base) {
    return -1;
  }
  *size = db->base->GetDiaryCount();
  return 0;
}

struct diary_items *allocate_diary_items(uint64_t size) {
  // TODO(yyt): buffer pool
  auto di = new diary_items;
  di->size = size;
  di->items = new diary_item[size];
  if (!di->items) {
    delete di;
    return nullptr;
  }
  for (uint64_t i = 0; i < di->size; ++i) {
    di->items[i].data.buffer = new char[kMaxBufferSize];
  }
  return di;
}

void release_diary_items(struct diary_items *di) {
  for (uint64_t i = 0; i < di->size; ++i) {
    delete[] di->items[i].data.buffer;
  }
  delete[] di->items;
  delete di;
}

int64_t list_diary(struct diary_base *db, uint64_t pos,
                   struct diary_items *items) {
  if (!db->base) {
    return -1;
  }
  return 0;
}

int get_diary(struct diary_base *db, uint64_t id, struct diary_items *items) {
  if (!db->base) {
    return -1;
  }

  return 0;
}

int put_diary(struct diary_base *db, char *buffer, uint64_t size) {
  if (size > kMaxBufferSize) {
    return -1;
  }
  return 0;
}