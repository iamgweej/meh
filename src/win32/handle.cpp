#include "win32/handle.h"

namespace meh {

void HandleDeleter::operator()(HANDLE h) { ::CloseHandle(h); }

} // namespace meh