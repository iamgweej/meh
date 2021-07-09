#pragma once

#include <Windows.h>

namespace meh {
namespace internals {

using KPRIORITY = DWORD;

struct CLIENT_ID {
  PVOID UniqueProcess;
  PVOID UniqueThread;
};

struct THREAD_BASIC_INFORMATION {
  NTSTATUS ExitStatus;
  PVOID TebBaseAddress;
  CLIENT_ID ClientId;
  KAFFINITY AffinityMask;
  KPRIORITY Priority;
  KPRIORITY BasePriority;
};

enum THREAD_INFORMATION_CLASS {
  ThreadBasicInformation,
};

using NtQueryInformationThread = NTSTATUS __stdcall(
    HANDLE ThreadHandle, THREAD_INFORMATION_CLASS ThreadInformationClass,
    PVOID ThreadInformation, ULONG ThreadInformationLength,
    PULONG ReturnLength);

} // namespace internals
} // namespace meh