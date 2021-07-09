#include <iostream>
#include <string>

#include "win32/module.h"
#include "win32/process.h"
#include "win32/thread.h"

struct _EXCEPTION_REGISTRATION {
  _EXCEPTION_REGISTRATION *prev;
  LPVOID *handler;
};

const auto LAST_EXCEPTION_REGISTRAR = reinterpret_cast<PVOID>(0xFFFFFFFF);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " [tid]" << std::endl;
    return 1;
  }

  DWORD tid = std::stoul(argv[1]);
  std::cout << "Thread id: " << tid << std::endl;

  auto thread = meh::Thread::FromThreadId(tid);

  auto pid = thread.ProcessId();
  std::cout << "Process Id: " << pid << std::endl;

  auto process = meh::Process::FromProcessId(pid);

  auto teb = thread.TEB();
  std::cout << "TEB: 0x" << std::hex << reinterpret_cast<size_t>(teb)
            << std::endl;

  LPVOID exception_list;
  process.ReadMemory(teb, &exception_list, sizeof(exception_list));
  std::cout << "Exception List: 0x" << std::hex
            << reinterpret_cast<size_t>(exception_list) << std::endl;

  PVOID prev_reg = exception_list;
  _EXCEPTION_REGISTRATION exc_reg;
  do {
    process.ReadMemory(prev_reg, &exc_reg, sizeof(exc_reg));
    std::cout << "Handler: 0x" << std::hex
              << reinterpret_cast<size_t>(exc_reg.handler) << std::endl;
    prev_reg = exc_reg.prev;
  } while (LAST_EXCEPTION_REGISTRAR != prev_reg);

  return 0;
}