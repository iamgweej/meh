#include <iostream>
#include <string>

#include "win32/thread.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " [tid]" << std::endl;
    return 1;
  }

  DWORD tid = std::stoul(argv[1]);
  std::cout << "Thread id: " << tid << std::endl;

  auto t = meh::Thread::FromThreadId(tid);
  std::cout << "Process Id: " << t.ProcessId() << std::endl;

  return 0;
}