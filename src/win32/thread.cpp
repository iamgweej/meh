#include "win32/thread.h"
#include "win32/handle.h"

#include <exception>
#include <utility>

#include "win32/internals/ntqueryinfothread.h"
#include "win32/module.h"

namespace meh {

Thread::Thread(UniqueHandle handle) : m_handle(std::move(handle)) {}

void Thread::Suspend() {
  if (static_cast<DWORD>(-1) == ::SuspendThread(m_handle.get())) {
    throw std::exception("Memes"); // TODO: Win32 exception
  }
}

PVOID Thread::TEB() {
  auto ntdll = Module::FromUnownedModule(::GetModuleHandleA("ntdll"));
  auto NtQueryInformationThread =
      ntdll.GetProcAddress<internals::NtQueryInformationThread *>(
          "NtQueryInformationThread");
  internals::THREAD_BASIC_INFORMATION info;
  if (0 != NtQueryInformationThread(m_handle.get(),
                                    internals::ThreadBasicInformation, &info,
                                    sizeof(info), nullptr)) {
    throw std::exception("Memes"); // TODO: NT excpetion.
  }

  return info.TebBaseAddress;
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