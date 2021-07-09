#include "win32/process.h"

#include <exception>

#include "win32/handle.h"

namespace meh {

Process::Process(UniqueHandle handle) : m_handle(std::move(handle)) {}

DWORD Process::Id() {
  return ::GetProcessId(m_handle.get()); // TODO: Check the return value?
}

SIZE_T Process::ReadMemory(PVOID where, PVOID buf, SIZE_T size) {
  SIZE_T read = 0;
  if (0 == ::ReadProcessMemory(m_handle.get(), where, buf, size, &read)) {
    throw std::exception("Memes"); // TODO: Win32 exception
  }
  return read;
}

Process Process::FromProcessId(DWORD pid, DWORD desired_access) {
  auto raw = ::OpenProcess(desired_access, FALSE, pid);
  if (NULL == raw) {
    throw std::exception("Memes"); // TODO: win32 exception
  }

  return Process(UniqueHandle(raw));
}

} // namespace meh