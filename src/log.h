#ifndef DIARYBASE_LOG_
#define DIARYBASE_LOG_

#include <iostream>

namespace diarybase_internal {

#define LOG(level) std::cout << "[" << #level << "]"

}

#endif