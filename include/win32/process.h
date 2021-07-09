#pragma once

#include "win32/handle.h"

namespace meh {

class Process {
public:
  Process(UniqueHandle handle);

  static Process FromProcessId(DWORD pid,
                               DWORD desired_access = PROCESS_ALL_ACCESS);

  DWORD Id();

  // Virtual Memory Functions
  SIZE_T ReadMemory(PVOID where, PVOID buf, SIZE_T size);

private:
  UniqueHandle m_handle;
};

} // namespace meh