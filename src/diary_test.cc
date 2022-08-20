#include "diarybase.h"

#include <iostream>

static const char kTestPath[] = "test";

int main() {
  auto db = create_diary(kTestPath, "test_diary", "yyt");
  if (!db) {
    std::cerr << "create diary error" << std::endl;
    return -1;
  }
  char buffer[] = "test123";
  int ret = put_diary(db, buffer, sizeof(buffer));
  if (ret) {
    std::cerr << "put diary error, ret: " << ret << std::endl;
    return -1;
  }
  return 0;
}