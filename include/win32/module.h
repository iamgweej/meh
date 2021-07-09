#pragma once

#include <exception>
#include <memory>

#include <Windows.h>

namespace meh {

class Module {
public:
  static Module FromOwnedModule(HMODULE handle);
  static Module FromUnownedModule(HMODULE handle);

  template <class T> T GetProcAddress(const char *proc) {
    // TODO: Check that T is a function?
    auto raw = ::GetProcAddress(m_handle.get(), proc);
    if (NULL == raw) {
      throw std::exception("Memes"); // TODO: Win32 exception
    }
    return reinterpret_cast<T>(raw);
  }

private:
  using UniqueModuleHandle =
      std::unique_ptr<std::remove_pointer_t<HMODULE>, decltype(&::FreeLibrary)>;

  static BOOL __stdcall NopFreeLibrary(HMODULE h);

  Module(UniqueModuleHandle handle);

  UniqueModuleHandle m_handle;
};

} // namespace meh