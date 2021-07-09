#pragma once

#include "win32/handle.h"
#include <memory>

#include <Windows.h>

namespace meh {

class HandleDeleter {
public:
  void operator()(HANDLE h);
};

using UniqueHandle =
    std::unique_ptr<std::remove_pointer_t<HANDLE>, HandleDeleter>;

} // namespace meh