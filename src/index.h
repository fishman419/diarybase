#ifndef DIARYBASE_INDEX_
#define DIARYBASE_INDEX_
#include <map>
#include <stdint.h>
#include <unordered_map>

namespace diarybase_internal {
class IndexTable {
public:
  IndexTable() {}
  ~IndexTable() {}

  int64_t GetPos(uint64_t id) {
    auto it = id2pos.find(id);
    if (it == id2pos.end()) {
      return -1;
    }
    return it->second;
  }

  void Insert(uint64_t id, uint64_t pos) { id2pos.emplace(id, pos); }

  void Remove(uint64_t id) { id2pos.erase(id); }

  uint64_t GetSize() { return id2pos.size(); }

private:
  std::unordered_map<uint64_t, uint64_t> id2pos;
};
} // namespace diarybase_internal

#endif