#pragma once

#include "win32/handle.h"

namespace meh {

class Thread {
public:
  Thread(UniqueHandle handle);

  void Suspend();
  DWORD ProcessId();

  // Internals functions
  PVOID TEB();

  static Thread FromThreadId(DWORD id,
                             DWORD desired_access = THREAD_ALL_ACCESS);

private:
  UniqueHandle m_handle;
};

} // namespace meh