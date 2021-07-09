#include "win32/thread.h"
#include "win32/handle.h"

#include <exception>
#include <utility>

namespace meh {

Thread::Thread(UniqueHandle handle) : m_handle(std::move(handle)) {}

void Thread::Suspend() {
  if (static_cast<DWORD>(-1) == ::SuspendThread(m_handle.get())) {
    throw std::exception("Memes"); // TODO: Win32 exception
  }
}

DWORD Thread::ProcessId() {
  DWORD pid = ::GetProcessIdOfThread(m_handle.get());
  if (0 == pid) {
    throw std::exception("Memes"); // TODO: Win32 exception
  }
  return pid;
}

Thread Thread::FromThreadId(DWORD id, DWORD desired_access) {
  HANDLE raw = ::OpenThread(desired_access, FALSE, id);
  if (NULL == raw) {
    throw std::exception("Memes"); // TODO: Win32 exception
  }
  return Thread(UniqueHandle(raw));
}

} // namespace meh