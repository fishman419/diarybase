#ifndef DIARYBASE_
#define DIARYBASE_

#include <stdint.h>

struct diary_base;

struct diary_data {
  char *buffer;
  uint64_t size;
};

struct diary_item {
  uint64_t id;
  uint64_t create_timestamp;
  uint64_t update_timestamp;
  struct diary_data data;
};

struct diary_items {
  struct diary_item *items;
  uint64_t size;
};

struct diary_base *create_diary(const char *path, const char *title,
                                const char *author);

struct diary_base *open_diary(const char *path);

int close_diary(struct diary_base *db);

int get_diary_size(struct diary_base *db, uint64_t *size);

struct diary_items *allocate_diary_items(uint64_t size);

void release_diary_items(struct diary_items *di);

int64_t list_diary(struct diary_base *db, uint64_t pos,
                   struct diary_items *items);

int get_diary(struct diary_base *db, uint64_t id, struct diary_items *items);

int put_diary(struct diary_base *db, const char *buffer, uint64_t size);

#endif