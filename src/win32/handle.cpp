#include "win32/handle.h"

namespace meh {

void HandleDeleter::operator()(HANDLE h) {
  if (NULL != h && INVALID_HANDLE_VALUE != h) {
    ::CloseHandle(h);
  }
}

} // namespace meh